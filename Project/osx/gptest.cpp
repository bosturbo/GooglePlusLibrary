#include <iostream>
#include <string>

#include <GooglePlusLibrary.hpp>

using namespace Gplusnasite::GooglePlusLibrary;
using namespace std;

int main(int argc, char* argv[])
{
	std::wcout.imbue(std::locale("C"));

    boost::shared_ptr<MyAccount> google_plus_my_account1(new MyAccount());

    google_plus_my_account1->getMainStream()->onPostAdded.connect([&](const Post& post)
    {
        wstring name = post.getAuthorName();
        wstring message = post.getMessage();
        wcout << name << L"さんがポストを投稿しました:" << message << endl;
    });
    google_plus_my_account1->getMainStream()->onPostEdited.connect([&](const Post& post)
    {
        wstring name = post.getAuthorName();
        wstring message = post.getMessage();
        wcout << name << L"さんがポストを編集しました:" << message << endl;
    });
    google_plus_my_account1->getMainStream()->onPostDeleted.connect([&](const wstring& post_id)
    {
        wcout << L"だれかがポストを削除しました" << endl;
    });
    google_plus_my_account1->getMainStream()->onCommentAdded.connect([&](const Comment& comment)
    {
        wstring name = comment.getCommentAuthorName();
        wstring message = comment.getCommentMessage();
        wcout << name << L"さんがコメントを投稿しました:" << message;
    });
    google_plus_my_account1->getMainStream()->onCommentEdited.connect([&](const Comment& comment)
    {
        wstring name = comment.getCommentAuthorName();
        wstring message = comment.getCommentMessage();
        wcout << name << L"さんがコメントを編集しました:" << message;
    });
    google_plus_my_account1->getMainStream()->onCommentDeleted.connect([&](const wstring& comment_id)
    {
        wcout << L"だれかがコメントを削除しました" << endl;
    });

    // example:hogehoge@gmail.com
    google_plus_my_account1->loginAsync(L"hogehoge", L"pass");
    // do something
    google_plus_my_account1->waitLoginAsync();

    cout << "終了するには何かを入力します";
    getchar();

    return 0;
}
