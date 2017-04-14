///////////////////////////////////////////////////////////
//  UserPriveleges.h
//  Implementation of the Enumeration UserPriveleges
//  Created on:      13-апр-2017 16:46:00
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_B0EC3481_A0A2_4ccf_8B17_95C72F41B804__INCLUDED_)
#define EA_B0EC3481_A0A2_4ccf_8B17_95C72F41B804__INCLUDED_

#include <string>

enum class UserPriveleges
{
	none = 0,
	guest = 1,
	user = 2,
	admin = 3
};

inline std::string UPtoS(const UserPriveleges& up)
{
	switch (up)
	{
	case UserPriveleges::guest: return "guest";
	case UserPriveleges::user: return "user";
	case UserPriveleges::admin: return "admin";
	default: return "none";
	}
}

inline UserPriveleges StoUP(const std::string& s)
{
	if (s == "guest") return UserPriveleges::guest;
	if (s == "user") return UserPriveleges::user;
	if (s == "admin") return UserPriveleges::admin;
	return UserPriveleges::none;
}

#endif // !defined(EA_B0EC3481_A0A2_4ccf_8B17_95C72F41B804__INCLUDED_)
