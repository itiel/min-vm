/* 
 . Author: Itiel Lopez - itiel@soyitiel.com
 . Created: 02/09/2021
*/

#ifndef _CHVAL_H_
#define _CHVAL_H_

/* -- Character validation macros -- */

// ch_is_lower     : a-z
// ch_is_upper     : A-Z
// ch_is_alph      : a-Z
// ch_is_dig       : 0-9
// ch_is_alphnum   : a-Z || 0-9
// ch_is_name_lead : _ || a-Z 
// ch_is_name      : _ || a-Z || 0-9
// ch_is_bin       : 0 || 1
// ch_is_oct       : 0-7
// ch_is_hex       : 0-9 || a-F 

#define      ch_is_lower(_ch) \
    (_ch >= 'a' && _ch <= 'z')
#define      ch_is_upper(_ch) \
    (_ch >= 'A' && _ch <= 'Z')
#define      ch_is_alph(_ch) \
    (ch_is_lower(_ch) || ch_is_upper(_ch)) 
#define       ch_is_dig(_ch) \
    (_ch >= '0' && _ch <= '9' )
#define   ch_is_alphnum(_ch) \
    (ch_is_alph(_ch) || ch_is_dig(_ch))
#define ch_is_name_lead(_ch) \
    (_ch == '_' || ch_is_alph(_ch))
#define      ch_is_name(_ch) \
    (_ch == '_' || ch_is_alphnum(_ch))
#define       ch_is_bin(_ch) \
    (_ch == '0' || _ch == '1')
#define       ch_is_oct(_ch) \
    (_ch >= '0' && _ch <= '7')
#define       ch_is_hex(_ch) \
    (ch_is_dig(_ch) || \
    (_ch >= 'a' && _ch <= 'f') || \
    (_ch >= 'A' && _ch <= 'F'))

#endif /* #ifndef _CHVAL_H_ */
