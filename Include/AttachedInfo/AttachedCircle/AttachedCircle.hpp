#pragma once

#ifdef _MSC_VER
#ifdef GOOGLEPLUSLIBRARY_EXPORTS
#define GOOGLEPLUSLIBRARY_API __declspec(dllexport)
#else
#define GOOGLEPLUSLIBRARY_API __declspec(dllimport)
#endif
#else
#define GOOGLEPLUSLIBRARY_API
#endif

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#pragma warning (disable:4996)
#endif
#endif

#include <Account/AccountList/AccountList.hpp>


#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Circle;
class MyAccount;
class JsonObject;

/*!
* @~english
* @brief Class to generate the information when added sharing circle to share post and to get information when the sharing circle has been attached to the post
* @~japanese
* @brief 投稿に付加されているサークル共有の情報を取得したり、サークル共有投稿をシェアするときの情報を生成するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AttachedCircle
{
	friend class AttachedCircleBase;
public:
	AttachedCircle();

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account_id account id(e.g. 116324207729009185938)
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief パラメーターからAttachedCircleを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_account_id アカウントID(例: 116324207729009185938)
	* @param circle_id サークルID(例: 6e1ff5b889ea6c7e)
	* @param is_include_yourself 共有サークルに自分を含めるかどうか
	* @return 生成されたAttachedCircle
	*/
	static AttachedCircle* create(const std::wstring& my_account_id, const std::wstring& circle_id, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account_id account id(e.g. 116324207729009185938)
	* @param circle Circle information you would like to share
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief パラメーターからAttachedCircleを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_account_id アカウントID(例: 116324207729009185938)
	* @param circle 共有したいサークル情報
	* @param is_include_yourself 共有サークルに自分を含めるかどうか
	*/
	static AttachedCircle* create(const std::wstring& my_account_id, const Circle& circle, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account Target account
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief パラメーターからAttachedCircleを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_account 対象のアカウント
	* @param circle_id サークルID(例: 6e1ff5b889ea6c7e)
	* @param is_include_yourself 共有サークルに自分を含めるかどうか
	*/
	static AttachedCircle* create(const MyAccount& my_account, const std::wstring& circle_id, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account Target account
	* @param circle Circle information you would like to share
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief パラメーターからAttachedCircleを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_account 対象のアカウント
	* @param circle 共有したいサークル情報
	* @param is_include_yourself 共有サークルに自分を含めるかどうか
	*/
	static AttachedCircle* create(const MyAccount& my_account, const Circle& circle, bool is_include_yourself = false);

public:
	const AccountList* getAccountList() const;
private:
	std::shared_ptr<AccountList> account_list_;

public:
	virtual ~AttachedCircle();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
