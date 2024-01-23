#include "Commands/messages.hpp"

std::string errorMessage(int key, std::string param1, std::string param2, std::string param3)
{
    if (key == 401) // 401    ERR_NOSUCHNICK "<nickname> :No such nick/channel"
    	return(":127.0.0.1 401 ERR_NOSUCHNICK " + param1 + " :No such nick/channel\r\n");
    
    if (key == 403) // 403    ERR_NOSUCHCHANNEL "<channel name> :No such channel"
    	return(":127.0.0.1 403 ERR_NOSUCHCHANNEL " + param1 + " :No such channel\r\n");    
    
    if (key == 404) // 404    ERR_CANNOTSENDTOCHAN "<channel name> :Cannot send to channel" 
    	return(":127.0.0.1 404 ERR_CANNOTSENDTOCHAN " + param1 + " :Cannot send to channel\r\n"); 
    
    if (key == 405) // 405    ERR_TOOMANYCHANNELS "<channel name> :You have joined too many channels"
    	return(":127.0.0.1 405 ERR_TOOMANYCHANNELS " + param1 + " :You have joined too many channels\r\n");  
    
    if (key == 407) // 407    ERR_TOOMANYTARGETS "<target> :<error code> recipients. <abort message>"
    	return(":127.0.0.1 403 ERR_TOOMANYTARGETS " + param1 + " :" + param2 + " recipients. " + param3 + "\r\n");  
    
    if (key == 411) // 411    ERR_NORECIPIENT ":No recipient given (<command>)"                
    	return(":127.0.0.1 411 ERR_NORECIPIENT :No recipient given (" + param1 + ")\r\n");  
    
    if (key == 412) // 412    ERR_NOTEXTTOSEND ":No text to send"
    	return(":127.0.0.1 412 ERR_NOTEXTTOSEND :No text to send\r\n");  
   
    if (key == 413) // 413    ERR_NOTOPLEVEL "<mask> :No toplevel domain specified"
    	return(":127.0.0.1 413 ERR_NOTOPLEVEL " + param1 + " :No toplevel domain specified\r\n");  
   
    if (key == 414) // 414    ERR_WILDTOPLEVEL "<mask> :Wildcard in toplevel domain"                
    	return(":127.0.0.1 414 ERR_WILDTOPLEVEL " + param1 + " :Wildcard in toplevel domain\r\n");
   
    if (key == 431) // 431    ERR_NONICKNAMEGIVEN ":No nickname given"           
    	return(":127.0.0.1 431 ERR_NONICKNAMEGIVEN :No nickname given\r\n");
   
    if (key == 432) // 432    ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname"
    	return(":127.0.0.1 432 ERR_ERRONEUSNICKNAME " + param1 + " :Erroneous nickname\r\n");
    
    if (key == 433) // 433    ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"   
    	return(":127.0.0.1 433 ERR_NICKNAMEINUSE " + param1 + " :Nickname is already in use\r\n");
   
    if (key == 436) // 436    ERR_NICKCOLLISION "<nick> :Nickname collision KILL from <user>@<host>"          
    	return(":127.0.0.1 436 ERR_NICKCOLLISION " + param1 + " :Nickname collision KILL from " + param2 + "@127.0.0.1\r\n");
   
    if (key == 437) // 437    ERR_UNAVAILRESOURCE "<nick/channel> :Nick/channel is temporarily unavailable"    
    	return(":127.0.0.1 437 ERR_UNAVAILRESOURCE " + param1 + " :Nick/channel is temporarily unavailable\r\n");
   
    if (key == 441) // 441    ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"            
    	return(":127.0.0.1 441 ERR_USERNOTINCHANNEL " + param1 + " " + param2 + " :They aren't on that channel\r\n");
   
    if (key == 442) // 442    ERR_NOTONCHANNEL "<channel> :You're not on that channel"
    	return(":127.0.0.1 442 ERR_NOTONCHANNEL " + param1 + " :You're not on that channel\r\n");
   
    if (key == 443) // 443    ERR_USERONCHANNEL "<user> <channel> :is already on channel"
    	return(":127.0.0.1 443 ERR_USERONCHANNEL " + param1 + " " + param2 + " :is already on channel\r\n");
   
    if (key == 461) // 461    ERR_NEEDMOREPARAMS "<command> :Not enough parameters"   
    	return(":127.0.0.1 461 ERR_NEEDMOREPARAMS " + param1 + " :Not enough parameters\r\n");
   
    if (key == 462) // 462    ERR_ALREADYREGISTRED ":Unauthorized command (already registered)" 
    	return(":127.0.0.1 462 PAERR_ALREADYREGISTRED :Unauthorized command (already registered)\r\n");
   
    if (key == 467) // 467    ERR_KEYSET "<channel> :Channel key already set" 
    	return(":127.0.0.1 467 ERR_KEYSET " + param1 + " :Channel key already set\r\n");
   
    if (key == 471) // 471    ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"    
    	return(":127.0.0.1 471 ERR_CHANNELISFULL " + param1 + " :Cannot join channel (+l)\r\n");
   
    if (key == 472) // 472    ERR_UNKNOWNMODE "<char> :is unknown mode char to me for <channel>"
    	return(":127.0.0.1 472 ERR_UNKNOWNMODE " + param1 + " :is unknown mode char to me for " + param2 + "\r\n");
  
    if (key == 473) // 473    ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)" 
    	return(":127.0.0.1 473 ERR_INVITEONLYCHAN " + param1 + " :Cannot join channel (+i)\r\n");
  
    if (key == 474) // 474    ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)"       
    	return(":127.0.0.1 474 ERR_BANNEDFROMCHAN " + param1 + " :Cannot join channel (+b)\r\n");
   
    if (key == 475) // 475    ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"  
    	return(":127.0.0.1 475 ERR_BADCHANNELKEY " + param1 + " :Cannot join channel (+k)\r\n");
   
    if (key == 476) // 476    ERR_BADCHANMASK "<channel> :Bad Channel Mask"  
    	return(":127.0.0.1 476 ERR_BADCHANMASK " + param1 + " :Bad Channel Mask\r\n");
    
    if (key == 477) // 477    ERR_NOCHANMODES "<channel> :Channel doesn't support modes" 
    	return(":127.0.0.1 477 ERR_NOCHANMODES " + param1 + " :Channel doesn't support modes\r\n");
   
    if (key == 482) // 482    ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
    	return(":127.0.0.1 482 ERR_CHANOPRIVSNEEDED " + param1 + " :You're not channel operator\r\n");
    
    if (key == 484) // 484    ERR_RESTRICTED ":Your connection is restricted!"
    	return(":127.0.0.1 484 ERR_RESTRICTED :Your connection is restricted!\r\n");
  
    else // 502    ERR_USERSDONTMATCH ":Cannot change mode for other users"
    	return(":127.0.0.1  502 ERR_USERSDONTMATCH :Cannot change mode for other users\r\n");                                                                                                                
}

std::string replyMessage(int key, std::string param1, std::string param2, std::string param3)
{
    if (key == 221) // 221    RPL_UMODEIS "<user mode string>"
        return (":127.0.0.1 221 RPL_UMODEIS " + param1 + "\r\n");

    if (key == 301) // 301    RPL_AWAY "<nick> :<away message>"
        return (":127.0.0.1 301 RPL_AWAY " + param1 + " :" + param2 + "\r\n");

    if (key == 324) // 324    RPL_CHANNELMODEIS "<channel> <mode> <mode params>"
        return (":127.0.0.1 324 RPL_CHANNELMODEIS " + param1 + " " + param2 + " " + param3 + "\r\n");

    if (key == 325) // 325    RPL_UNIQOPIS "<channel> <nickname>"
        return (":127.0.0.1 325 RPL_UNIQOPIS " + param1 + " " + param2 + "\r\n");

    if (key == 331) // 331    RPL_NOTOPIC "<channel> :No topic is set" 
        return (":127.0.0.1 331 RPL_NOTOPIC " + param1 + " :No topic is set\r\n");   

    if (key == 332) // 332    RPL_TOPIC "<channel> :<topic>"
        return (":127.0.0.1 332 RPL_TOPIC " + param1 + " :" + param2 + "\r\n"); 

    if (key == 341) // 341    RPL_INVITING "<channel> <nick>"
        return (":127.0.0.1 341 RPL_INVITING " + param1 + " " + param2 + "\r\n");   

    if (key == 346) // 346    RPL_INVITELIST "<channel> <invitemask>"    
        return (":127.0.0.1 346 RPL_INVITELIST " + param1 + " " + param2 + "\r\n");    

    if (key == 347) // 347    RPL_ENDOFINVITELIST "<channel> :End of channel invite list"
        return (":127.0.0.1 347 RPL_ENDOFINVITELIST " + param1 + " :End of channel invite list\r\n"); 

    if (key == 348) // 348    RPL_EXCEPTLIST "<channel> <exceptionmask>"    
        return (":127.0.0.1 348 RPL_EXCEPTLIST " + param1 + " " + param2 + "\r\n"); 

    if (key == 349) // 349    RPL_ENDOFEXCEPTLIST "<channel> :End of channel exception list"
        return (":127.0.0.1 349 RPL_ENDOFEXCEPTLIST " + param1 + " :End of channel exception list\r\n"); 

    if (key == 367) // 367    RPL_BANLIST "<channel> <banmask>"         
        return (":127.0.0.1 367 RPL_BANLIST " + param1 + " " + param2 + "\r\n");          

    if (key == 368) // 368    RPL_ENDOFBANLIST "<channel> :End of channel ban list"
        return (":127.0.0.1 368 RPL_ENDOFBANLIST " + param1 + " :End of channel ban list\r\n"); 

    return ("Nothing");
}