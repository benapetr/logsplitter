#include "../include/Configuration.h"

int Configuration::Verbosity = 1;

string Configuration::DefaultProjectPath = "/data/project";

// Path where merged files are stored
string Configuration::DefaultGlobalPath = "/data/project/.system/logs/apache2/global_access.log";

string Configuration::DefaultPublicPath = "/data/project/.system/logs/public_apache2/global_access.log";

string Configuration::MissingPath = "/var/log/apache2/lost.log";

string Configuration::OtherPath = "/var/log/apache2/access.log";
