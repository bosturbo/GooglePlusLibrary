GooglePlusLibrary
======================
 ネイティブC++デスクトップアプリケーションからGoogle+に関するさまざまな項目を操作することができます  
 Unofficial Google+ API Library for Native C++ 

 Google+のクライアントソフトなどをWin32APIやQt, XCodeなどで作ることができます  
 You can create applications for Google+ Client. 
 
 動作環境は特に問いません(PC環境で動作します)  
 Operating environment can be anything(PC only). 
 
 開発環境にはboostライブラリなどが必要です(協力の項 参考)  
 The development environment is required boost libraries and other libraries. 
 
 まだまだバグがあるため、積極的にバグフィックスしてもらえると助かります  
 This Library has many bugs, so Please Bug Fix. Thank you.  
 
機能(Function)
--------
### ログイン(Login)
  ・ログイン(Login)  
関連情報(Informations)
--------
### 連絡先(Contacts)
1. [Google+ Account](https://plus.google.com/u/0/116324207729009185938/about "Google+アカウント(Google+ Account)")
    * ![Account Image](https://lh5.googleusercontent.com/-_u67HqR0D8g/AAAAAAAAAAI/AAAAAAAAEtk/EnkyO0_5ElY/photo.jpg?sz=90 "アカウント画像(Account Image)")

ライセンス(License)
----------
Library : 修正BSDライセンス(New BSD License)  
Copyright &copy; 2012 Mori Satoshi, All Rights Reserved.  

協力・必要環境(Cooperation/Required Libraries) 
---------- 
boost (Boost Software License)  
(http://www.boost.org/) 

GooglePlusJsonParser (New BSD License)  
(https://github.com/gplusnasite/GooglePlusJsonParser) 

Lua (MIT license)  
(http://www.lua.org/) 

Luabind (MIT License)  
(http://www.rasterbar.com/products/luabind.html) 

UTF-8 CPP (調査中)  
(http://sourceforge.net/projects/utfcpp/) 

最初の一歩(Get Started)
--------
```cpp
#include <tchar.h>

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#endif
#endif

#include <iostream>
#include <string>

#include <GooglePlusLibrary.hpp>

using namespace Gplusnasite::GooglePlusLibrary;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout.imbue(std::locale("japanese"));
	
	boost::shared_ptr<MyAccount> google_plus_my_account1(new MyAccount());
	
	// example:hogehoge@gmail.com
	google_plus_my_account1->loginAsync(L"hogehoge", L"pass");
	// do something
	google_plus_my_account1->waitLoginAsync();
	
	cout << "終了するには何かを入力します";
	getchar();
	return 0;
}

```

次の一歩(Next Step)
--------
```cpp
#include <tchar.h>

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#endif
#endif

#include <iostream>
#include <string>

#include <GooglePlusLibrary.hpp>

using namespace Gplusnasite::GooglePlusLibrary;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout.imbue(std::locale("japanese"));

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
```