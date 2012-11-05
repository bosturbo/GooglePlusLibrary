#include <Stream/Post/PostSetter.hpp>

#include <AttachedInfo/AttachedAlbum/AttachedAlbumSetter.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircleSetter.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideoSetter.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocationSetter.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultSetter.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrlSetter.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylistSetter.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

void PostSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<PostSetter>("PostSetter")
			.def(constructor<>())
			.def("setPostType", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setPostType))
			.def("setAuthorName", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setAuthorName))
			.def("setAccountID", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setAccountID))
			.def("setAccountImageUrl", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setAccountImageUrl))
			.def("setIsResharedPost", &PostSetter::setIsResharedPost)
			.def("setAttachedAlbum", static_cast<void(PostSetter::*)(AttachedAlbumSetter&)>(&PostSetter::setAttachedAlbum))
			.def("setAttachedCircle", static_cast<void(PostSetter::*)(AttachedCircleSetter&)>(&PostSetter::setAttachedCircle))
			.def("setAttachedImageVideo", static_cast<void(PostSetter::*)(AttachedImageVideoSetter&)>(&PostSetter::setAttachedImageVideo))
			.def("setAttachedLocation", static_cast<void(PostSetter::*)(AttachedLocationSetter&)>(&PostSetter::setAttachedLocation))
			.def("setAttachedSearchResult", static_cast<void(PostSetter::*)(AttachedSearchResultSetter&)>(&PostSetter::setAttachedSearchResult))
			.def("setAttachedUrl", static_cast<void(PostSetter::*)(AttachedUrlSetter&)>(&PostSetter::setAttachedUrl))
			.def("setAttachedYouTubePlaylist", static_cast<void(PostSetter::*)(AttachedYouTubePlaylistSetter&)>(&PostSetter::setAttachedYouTubePlaylist))
			.def("setOriginalPostID", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setOriginalPostID))
			.def("setOriginalPostMessage", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setOriginalPostMessage))
			.def("setOriginalPostUrl", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setOriginalPostUrl))
			.def("setPostID", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setPostID))
			.def("setPostUrl", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setPostUrl))
			.def("setPlusOneID", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setPlusOneID))
			.def("setPostTime", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setPostTime))
			.def("setIsPublicPost", &PostSetter::setIsPublicPost)
			.def("setMessage", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setMessage))
			.def("setIsMobilePost", &PostSetter::setIsMobilePost)
			.def("setIsCommentDisabled", &PostSetter::setIsCommentDisabled)
			.def("setIsLockdPost", &PostSetter::setIsLockdPost)
			.def("setIsMyPost", &PostSetter::setIsMyPost)
			.def("setIsEdited", &PostSetter::setIsEdited)
			.def("setLastEditedTime", static_cast<void(PostSetter::*)(const string&)>(&PostSetter::setLastEditedTime))
		];
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite