#include "../include/Configuration.h"

int Configuration::Verbosity = 1;

// Path where the project local files are stored
string Configuration::DefaultProjectPath = "/tmp/project";

// Path where merged files are stored
string Configuration::DefaultGlobalPath = "/tmp/project/.system/logs/apache2/global_access.log";

string Configuration::DefaultPublicPath = "/tmp/project/.system/logs/public_apache2/global_access.log";

string Configuration::MissingPath = "/tmp/log/apache2/lost.log";

string Configuration::OtherPath = "/tmp/log/apache2/access.log";

/*
tring Configuration::DefaultProjectPath = "/data/project";

// Path where merged files are stored
string Configuration::DefaultGlobalPath = "/data/project/.system/logs/apache2/global_access.log";

string Configuration::DefaultPublicPath = "/data/project/.system/logs/public_apache2/global_access.log";

string Configuration::MissingPath = "/var/log/apache2/lost.log";

string Configuration::OtherPath = "/var/log/apache2/access.log";
*/
