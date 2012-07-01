/* OpenSSL headers */
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

/* Size definitions */
#define BUFRECVSIZE 1024
#define RESPONSE_SIZE 40960
#define REQUEST_SIZE 1024
#define SESSION_SIZE 512
#define MAX_MESSAGE_LENGTH 140
#define API_KEY_LENGTH 64

/* structures */
typedef struct plurk_struct {
	char recvbuf[BUFRECVSIZE];
	char reply[RESPONSE_SIZE];
	char *header, *body;
	char url[REQUEST_SIZE];
	char session[SESSION_SIZE];
	char encmsg[MAX_MESSAGE_LENGTH * 3];
	char apikey[API_KEY_LENGTH];
	unsigned int sestate;		/* if session has been initialized */

	unsigned int sstate;   		/* if SSL has been initialized */
	SSL_CTX *ctx;
	BIO *bio;
} PLURK;

/* Public Plurk APIs */
PLURK *plurk_open(const char *key);
void plurk_close(PLURK *ph);
int plurk_login(PLURK *ph, const char *username, const char *password);
int plurk_logout(PLURK *ph);
int plurk_add(PLURK *ph, const char *content, const char *qualifier, const char *limit_list);
int plurk_resps_get(PLURK *ph, const char *plurk_id, const char *from_responses);
int plurk_oprofile_get(PLURK *ph);
int plurk_pprofile_get(PLURK *ph, const char *user_id);
int plurk_pprofile_get_byint(PLURK *ph, long long int user_id);
int plurk_resps_radd(PLURK *ph, const char *plurk_id, const char *content, const char *qualifier);
int plurk_polling_getplurks(PLURK *ph, const char *offset, int limit);
int plurk_timeline_getplurks(PLURK *ph, const char *offset, int limit);
/* some extra APIs by xatier */
/* /API/Polling/getUnreadCount */
int plurk_polling_getUnreadCount(PLURK *ph);
/* /API/Timeline/getPlurk */
int plurk_timeline_getPlurk(PLURK *ph, const char *plurk_id);
/* /API/Timeline/getUnreadPlurks */
int plurk_timeline_getUnreadPlurks(PLURK *ph);
/* /API/Timeline/plurkDelete  */
int plurk_timeline_plurkDelete(PLURK *ph, const char *plurk_id);
/* /API/Timeline/plurkEdit */
int plurk_timeline_plurkEdit(PLURK *ph, const char *plurk_id, const char *content);
/* /API/Timeline/mutePlurks */
int plurk_timeline_mutePlurks(PLURK *ph, const char *ids);
/* /API/Timeline/unmutePlurks */
int plurk_timeline_unmutePlurks(PLURK *ph, const char *ids);
/* /API/Timeline/favoritePlurks */
int plurk_timeline_favoritePlurks(PLURK *ph, const char *ids);
/* /API/Timeline/unfavoritePlurks */
int plurk_timeline_unfavoritePlurks(PLURK *ph, const char *ids);
/* /API/Timeline/markAsRead */
int plurk_timeline_markAsRead(PLURK *ph, const char *ids);

