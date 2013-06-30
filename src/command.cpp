#include <qredis/command.h>
#include "command_p.h"

using namespace QRedis;

Command::Command(QObject * parent)
    : QObject(parent), d(new CommandPrivate)
{
}

Command::~Command()
{
}
