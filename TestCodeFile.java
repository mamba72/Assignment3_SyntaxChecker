package MatchingEngine;

import MySqlInteraction.SQL;
import OrderInfo.*;
import net.sf.saxon.expr.TryCatch;
import quickfix.FieldNotFound;
import quickfix.SessionID;
import quickfix.field.OrdType;
import quickfix.field.Side;
import quickfix.field.Symbol;
import quickfix.field.TimeInForce;
import quickfix.fix40.NewOrderSingle;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.sql.SQLException;
import java.util.ArrayList;


public class Matching implements OrderListener {

    private static Matching singleton_instance = null;

    private static Logger logger;
    private static Thread loggingThread;
    private static SQL sql;

    public SecurityList securities = null;
    public OrderList orders = null;
    public TradeList trades = null;
    public UserList users = null;



    /**
     * This is the default constructor. Only use this if you know what you're doing.
     * There are other classes being used that need the static elements of this class,
     * but these elements aren't initialized in this constructor.
     */
    //public Matching() {}

    private Matching(Settings settings)
    {
        logger = new Logger(settings);

        logger.setFlushSleepTimer(Integer.parseInt(
                settings.getSetting("loggerFlushSleepTimer", "60000")));

        loggingThread = startAutoLogging(logger);
        try
        {
            sql = new SQL(settings);
        }catch (InvalidPropertyException e)
        {
            logger.logException(e, "SQL constructor failed.");
        }

        try
        {
            sql.makeConnection();
        }
        catch (SQLException e)
        {
            logger.logException(e, "Could not make connection.");
            logger.log("Failed to make connection to SQL server. Shutting down.");
            System.exit(-1);
        }
        catch (ClassNotFoundException e)
        {
            logger.logException(e, "Could not find class com.mysql.jdbc.Driver");
        }

        securities = new SecurityList();
        orders = new OrderList();
        trades = new TradeList();
        users = new UserList("userList");

    }

    /**
     * This function is to ensure that only one matching object exists at a time.
     * @param settings
     * @return
     */
    public static Matching getInstance(Settings settings)
    {
        if(singleton_instance == null)
            singleton_instance = new Matching(settings);

        return singleton_instance;
    }

    /**
     * This function is to ensure that only one matching object exists at a time.
     * @return
     */
    public static Matching getInstance() throws MatchingEngineNotInitializedException
    {
        if(singleton_instance == null)
            throw new MatchingEngineNotInitializedException("You must first provide the settings object " +
                    "in order to create the object in the first place.");

        return singleton_instance;
    }

    public static SQL getSql() {
        return sql;
    }

    /**
     * This will be the main of the class pretty much
     */
    public void startMatching()
    {

        try {
            logger.setVerbosity(1);
        }catch (InvalidVerbosityException e)
        {
            e.printStackTrace();
        }

        OrderStatusUpdaterThread orderStatusUpdaterThread = new OrderStatusUpdaterThread();
        orderStatusUpdaterThread.setName("Order Status Updater Thread");
        orderStatusUpdaterThread.setPriority(4);
        orderStatusUpdaterThread.start();

        MatcherThread matcherThread = new MatcherThread();
        matcherThread.setName("MatcherThread");
        matcherThread.setPriority(10);
        matcherThread.start();



        System.out.println("End of matching engine.");
    }

    /**
     * This returns the logger that the matching object is using.
     * NOTE: this will return null if there is no logger initialized by the matching class
     * @return logger
     */
    public static Logger getLogger()
    {
        return logger;
    }

    private Logger setLogger(Logger logger)
    {
        this.logger = logger;
        return this.logger;
    }

    private Logger setLogger(Settings settings)
    {
        this.logger = new Logger(settings);
        return this.logger;
    }

    /**
     * This will start the 2 logging threads. (one to log, one to flush)
     * @param logger
     * @return
     */
    private static Thread startAutoLogging(Logger logger)
    {
        Thread loggingThread = new Thread(logger);
        loggingThread.setName("Logging Thread");
        //this should probably be changed to true after the matching engine is actually implemented.
        loggingThread.setDaemon(false);

        loggingThread.start();

        return loggingThread;
    }

    /**
     * The exact same thing as the other autoLogging function but with a custom name.
     * @param logger
     * @param threadName
     * @return
     */
    public static Thread startAutoLogging(Logger logger, String threadName)
    {
        Thread loggingThread = new Thread(logger);
        loggingThread.setName(threadName);
        //this should probably be changed to true after the matching engine is actually implemented.
        loggingThread.setDaemon(false);

        loggingThread.start();

        return loggingThread;
    }



    public static InputStream getSettingsInputStream(String[] args) throws FileNotFoundException {
        InputStream inputStream = null;
        if (args.length == 0) {
            inputStream = Matching.class.getResourceAsStream("MatchingEngine.cfg");
        } else if (args.length == 1) {
            inputStream = new FileInputStream(args[0]);
        }
        if (inputStream == null) {
            System.out.println("usage: " + Matching.class.getName() + " [configFile].");
            System.exit(1);
        }
        return inputStream;
    }


    @Override
    public Object anOrderWasReceived(Object order, String fixVersion)
    {

        logger.log("An order was received! FIX Version: " + fixVersion);
        try
        {
            orders.add(order, fixVersion);
        }catch (FieldNotFound e)
        {
            logger.logException(e, "Could not add order to list of orders.");
        }

        return order;
    }

    @Override
    public void serverUpAndRunning()
    {
        logger.log("The FIX server is up and running.");
    }

    @Override
    public SessionID someoneLoggedOn(SessionID sessionID) {

        logger.log("Someone logged on with the following name and session ID: " + sessionID.getTargetCompID() + " , " + sessionID.toString());

        return sessionID;
    }

    //this thread is supposed to run forever.
    private class MatcherThread extends Thread
    {

        @Override
        public void run()
        {
            try {
                //FIGURE OUT HOW TO MAKE THEM TIMEOUT!
                ArrayList<Order> timeoutList;

                int nextBuyIndex = 0;

                while (true) {
                    if (orders.size() > 1) {

                        Order order = orders.get(nextBuyIndex);

                        boolean foundMatch = false;

                        //logger.log("Order info: " + order.getSymbol() + " " + order.getQuantity());

                        if(order.getSide().equals(OrderSide.BUY))
                        {
                            for(int i = 1; i < orders.size(); i++)
                            {
                                if(order.getSymbol().equals(orders.get(i).getSymbol()))
                                {
                                    if(orders.get(i).getSide().equals(OrderSide.SELL))
                                    {

                                        logger.log("Found a match: " + order.getSymbol() + " " + order.getSide() + " / " + orders.get(i).getSymbol() + " " + orders.get(i).getSide());

                                        orders.removeByIndex(i);
                                        orders.removeByIndex(nextBuyIndex);

                                        logger.log("Removed orders at index " + nextBuyIndex + " and " + i);
                                        foundMatch = true;
                                        break;//stop finding matches.
                                    }
                                }
                            }

                            if(foundMatch == false)
                            {
                                orders.removeByIndex(nextBuyIndex);
                            }

                        }
                        else
                        {
                            nextBuyIndex++;
                        }



                    } else {
                        Thread.sleep(0,1);
                    }

                }
            }catch (InterruptedException e)
            {
                logger.logException(e, "Matcher Thread was interrupted.");
            }
        }
    }


    private class OrderStatusUpdaterThread extends Thread
    {
        @Override
        public void run()
        {
            while(true)
            {
                try
                {
                    Thread.sleep(10000);//every 10 seconds
                    logger.log("Current Number of Orders: " + orders.size());
                }catch (InterruptedException e)
                {
                    logger.logException(e, "Updater Thread was interrupted.");
                }

            }
        }
    }

}
