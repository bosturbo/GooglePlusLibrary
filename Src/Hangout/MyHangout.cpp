#include <Hangout/MyHangout.hpp>
#include <Hangout/GroupChat.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

MyHangout::MyHangout()
:group_chat_(make_shared<GroupChat>())
{
}

MyHangout::~MyHangout()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite