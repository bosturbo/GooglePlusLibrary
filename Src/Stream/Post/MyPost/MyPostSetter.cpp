#include <Stream/Post/MyPost/MyPostSetter.hpp>
#include <Stream/Post/PostSetter.hpp>

#include <Utility/Utility.hpp>

#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

MyPostSetter::MyPostSetter()
{
}

void MyPostSetter::setPostType(const string& post_type)
{
	setPostType(Utility::convertUTF8ToUnicode(post_type));
}

void MyPostSetter::setPostType(const wstring& post_type)
{
	post_setter_(my_post_)->setPostType(post_type);
}

void MyPostSetter::setAuthorName(const string& author_name)
{
	setAuthorName(Utility::convertUTF8ToUnicode(author_name));
}

void MyPostSetter::setAuthorName(const wstring& author_name)
{
	post_setter_(my_post_)->setAuthorName(author_name);
}

void MyPostSetter::setAccountID(const string& account_id)
{
	setAccountID(Utility::convertUTF8ToUnicode(account_id));
}

void MyPostSetter::setAccountID(const wstring& account_id)
{
	post_setter_(my_post_)->setAccountID(account_id);
}

void MyPostSetter::setAccountImageUrl(const string& account_image_url)
{
	setAccountImageUrl(Utility::convertUTF8ToUnicode(account_image_url));
}

void MyPostSetter::setAccountImageUrl(const wstring& account_image_url)
{
	post_setter_(my_post_)->setAccountImageUrl(account_image_url);
}

void MyPostSetter::setIsResharedPost(bool is_shared_post)
{
	post_setter_(my_post_)->setIsResharedPost(is_shared_post);
}

void MyPostSetter::setAttachedAlbum(const AttachedAlbum& attached_album)
{
	post_setter_(my_post_)->setAttachedAlbum(attached_album);
}

void MyPostSetter::setAttachedCircle(const AttachedCircle& attached_circle)
{
	post_setter_(my_post_)->setAttachedCircle(attached_circle);
}

void MyPostSetter::setAttachedImageVideo(const AttachedImageVideo& attached_image_video)
{
	post_setter_(my_post_)->setAttachedImageVideo(attached_image_video);
}

void MyPostSetter::setAttachedLocation(const AttachedLocation& attached_location)
{
	post_setter_(my_post_)->setAttachedLocation(attached_location);
}

void MyPostSetter::setAttachedSearchResult(const AttachedSearchResult& attached_search_result)
{
	post_setter_(my_post_)->setAttachedSearchResult(attached_search_result);
}

void MyPostSetter::setAttachedUrl(const AttachedUrl& attached_url)
{
	post_setter_(my_post_)->setAttachedUrl(attached_url);
}

void MyPostSetter::setAttachedYouTubePlaylist(const AttachedYouTubePlaylist& attached_youtube_play_list)
{
	post_setter_(my_post_)->setAttachedYouTubePlaylist(attached_youtube_play_list);
}

void MyPostSetter::setOriginalPostID(const string& original_post_id)
{
	setOriginalPostID(Utility::convertUTF8ToUnicode(original_post_id));
}

void MyPostSetter::setOriginalPostID(const wstring& original_post_id)
{
	post_setter_(my_post_)->setOriginalPostID(original_post_id);
}

void MyPostSetter::setOriginalPostMessage(const string& original_post_message)
{
	setOriginalPostMessage(Utility::convertUTF8ToUnicode(original_post_message));
}

void MyPostSetter::setOriginalPostMessage(const wstring& original_post_message)
{
	post_setter_(my_post_)->setOriginalPostMessage(original_post_message);
}

void MyPostSetter::setOriginalPostUrl(const string& original_post_url)
{
	setOriginalPostUrl(Utility::convertUTF8ToUnicode(original_post_url));
}

void MyPostSetter::setOriginalPostUrl(const wstring& original_post_url)
{
	post_setter_(my_post_)->setOriginalPostUrl(original_post_url);
}

void MyPostSetter::setPostID(const string& post_id)
{
	setPostID(Utility::convertUTF8ToUnicode(post_id));
}

void MyPostSetter::setPostID(const wstring& post_id)
{
	post_setter_(my_post_)->setPostID(post_id);
}

void MyPostSetter::setPostUrl(const string& post_url)
{
	setPostUrl(Utility::convertUTF8ToUnicode(post_url));
}

void MyPostSetter::setPostUrl(const wstring& post_url)
{
	post_setter_(my_post_)->setPostUrl(post_url);
}

void MyPostSetter::setPlusOneID(const string& plus_one_id)
{
	setPlusOneID(Utility::convertUTF8ToUnicode(plus_one_id));
}

void MyPostSetter::setPlusOneID(const wstring& plus_one_id)
{
	post_setter_(my_post_)->setPlusOneID(plus_one_id);
}

void MyPostSetter::setPostTime(const boost::posix_time::ptime& post_time)
{
	post_setter_(my_post_)->setPostTime(post_time);
}

void MyPostSetter::setIsPublicPost(bool is_public_post)
{
	post_setter_(my_post_)->setIsPublicPost(is_public_post);
}

void MyPostSetter::setMessage(const string& message)
{
	setMessage(Utility::convertUTF8ToUnicode(message));
}

void MyPostSetter::setMessage(const wstring& message)
{
	post_setter_(my_post_)->setMessage(message);
}

void MyPostSetter::setIsMobilePost(bool is_mobile_post)
{
	post_setter_(my_post_)->setIsMobilePost(is_mobile_post);
}

void MyPostSetter::setIsCommentDisabled(bool is_comment_disabled)
{
	post_setter_(my_post_)->setIsCommentDisabled(is_comment_disabled);
}

void MyPostSetter::setIsLockdPost(bool is_lock_post)
{
	post_setter_(my_post_)->setIsLockdPost(is_lock_post);
}

void MyPostSetter::setIsMyPost(bool is_my_post)
{
	post_setter_(my_post_)->setIsMyPost(is_my_post);
}

void MyPostSetter::setIsEdited(bool is_edited)
{
	post_setter_(my_post_)->setIsEdited(is_edited);
}

void MyPostSetter::setLastEditedTime(const boost::posix_time::ptime& last_edited_time)
{
	post_setter_(my_post_)->setLastEditedTime(last_edited_time);
}
/*
MyPost MyPostSetter::toPost()
{
	return my_post_;
}
*/
void MyPostSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<MyPostSetter>("MyPostSetter")
			.def(constructor<>())
			.def("setPostType", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setPostType))
			.def("setAuthorName", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setAuthorName))
			.def("setAccountID", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setAccountID))
			.def("setAccountImageUrl", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setAccountImageUrl))
			.def("setIsResharedPost", &MyPostSetter::setIsResharedPost)
			.def("setAttachedAlbum", &MyPostSetter::setAttachedAlbum)
			.def("setAttachedCircle", &MyPostSetter::setAttachedCircle)
			.def("setAttachedImageVideo", &MyPostSetter::setAttachedImageVideo)
			.def("setAttachedLocation", &MyPostSetter::setAttachedLocation)
			.def("setAttachedSearchResult", &MyPostSetter::setAttachedSearchResult)
			.def("setAttachedUrl", &MyPostSetter::setAttachedUrl)
			.def("setAttachedYouTubePlaylist", &MyPostSetter::setAttachedYouTubePlaylist)
			.def("setOriginalPostID", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setOriginalPostID))
			.def("setOriginalPostMessage", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setOriginalPostMessage))
			.def("setOriginalPostUrl", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setOriginalPostUrl))
			.def("setPostID", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setPostID))
			.def("setPostUrl", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setPostUrl))
			.def("setPlusOneID", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setPlusOneID))
			.def("setIsPublicPost", &MyPostSetter::setIsPublicPost)
			.def("setMessage", static_cast<void(MyPostSetter::*)(const string&)>(&MyPostSetter::setMessage))
			.def("setIsMobilePost", &MyPostSetter::setIsMobilePost)
			.def("setIsCommentDisabled", &MyPostSetter::setIsCommentDisabled)
			.def("setIsLockdPost", &MyPostSetter::setIsLockdPost)
			.def("setIsMyPost", &MyPostSetter::setIsMyPost)
			.def("setIsEdited", &MyPostSetter::setIsEdited)
		];
}

MyPostSetter::~MyPostSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite