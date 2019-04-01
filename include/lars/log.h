
#include <iostream>


#define LARS_LOG_WITH_PROMPT(value,prompt) do{ std::cout << prompt << value << std::endl;  }while(0)

#define LARS_LOG(value) do{ std::cout << "lars: log: " << value << std::endl;  }while(0)
#define LARS_LOGV(value) LARS_LOG(#value << " = " << value)
#define LARS_LOGT() LARSLOG("reached " << ::app::log_helper::file_name(__FILE__) << ":" << __LINE__ << " with function \"" << __PRETTY_FUNCTION__ << "\"" )
