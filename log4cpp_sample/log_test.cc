/*
 * log_test.cc
 *
 *  Created on: 2016年7月18日
 *      Author: miaohongyuan
 */

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

int main(int argc, char* argv[])
{
    std::string initFileName = "log4cpp.properties";
    log4cpp::PropertyConfigurator::configure(initFileName);

    log4cpp::Category& root = log4cpp::Category::getRoot();

    log4cpp::Category& sub1 =
        log4cpp::Category::getInstance(std::string("sub1"));

    log4cpp::Category& sub2 =
        log4cpp::Category::getInstance(std::string("sub1.sub2"));

    root.warn("Storm is coming");

    sub1.debug("Received storm warning");
    sub1.info("Closing all hatches");

    sub2.debug("Hiding solar panels");
    sub2.error("Solar panels are blocked");
    sub2.debug("Applying protective shield");
    sub2.warn("Unfolding protective shield");
    sub2.info("Solar panels are shielded");

    sub1.info("All hatches closed");

    root.info("Ready for storm.");

    log4cpp::Category::shutdown();

    return 0;
}


/*
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"

int main(int argc, char* argv[]) {
    log4cpp::Layout* layout = new log4cpp::BasicLayout();
    log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender", "./test_log4cpp1.log");
    appender->setLayout(layout);
    log4cpp::Category& warn_log = log4cpp::Category::getInstance("mywarn");
    warn_log.setAdditivity(false);
    warn_log.setAppender(appender);
    warn_log.setPriority(log4cpp::Priority::WARN);
    warn_log.info("INFO message.");
    warn_log.debug("DEBUG message.");
    warn_log.alert("ALERT message.");

    warn_log.log(log4cpp::Priority::WARN, "WARN message of other print style.");
    log4cpp::Priority::PriorityLevel priority;
    bool this_is_critical = true;
    if (this_is_critical)
        priority = log4cpp::Priority::CRIT;
    else
        priority = log4cpp::Priority::DEBUG;
    warn_log.log(priority, "Log level depend on context.");

    warn_log.critStream() << "This is show up << as "
            << 1 << " critical message";
    log4cpp::Category::shutdown();

    return 0;
}
*/


