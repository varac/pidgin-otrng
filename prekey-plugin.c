#include "prekey-plugin.h"

/* libpurple */
#include "connection.h"
#include "prpl.h"

#include <libotr-ng/messaging.h>

extern otrng_user_state_s *otrng_userstate;

otrng_prekey_client_s *otrng_plugin_get_prekey_client(PurpleAccount *account) {
  // TODO: Probably needs the info from the service discovery
  //- Service identifier
  //- Service fingerprint
  otrng_client_s *client = otrng_messaging_client_get(otrng_userstate, account);
  if (!client) {
    return NULL;
  }

  return otrng_client_get_prekey_client(client);
}

gboolean otrng_plugin_receive_prekey_protocol_message(char **tosend,
                                                      const char *server,
                                                      const char *message,
                                                      PurpleAccount *account) {
  otrng_prekey_client_s *prekey_client = NULL;

  prekey_client = otrng_plugin_get_prekey_client(account);
  if (!prekey_client) {
    return FALSE;
  }

  return otrng_prekey_client_receive(tosend, server, message, prekey_client);
}

static void account_signed_on_cb(PurpleConnection *conn, void *data) {
  // TODO: Query the server from service discovery and fallback to
  //"prekeys.<domainpart>" server.
#ifdef DEFAULT_PREKEYS_SERVER
  const char *prekeys_server = DEFAULT_PREKEYS_SERVER;
#else
  const char *prekeys_server = "";
#endif

  PurpleAccount *account = purple_connection_get_account(conn);
  char *message = NULL;

  otrng_prekey_client_s *prekey_client =
      otrng_plugin_get_prekey_client(account);
  if (!prekey_client) {
    return;
  }

  message = otrng_prekey_client_request_storage_status(prekey_client);
  serv_send_im(conn, prekeys_server, message, 0);
  free(message);
}

gboolean otrng_prekey_plugin_load(PurplePlugin *handle) {
  if (!otrng_userstate) {
    return FALSE;
  }

  /* Watch to the connect event of every account */
  purple_signal_connect(purple_connections_get_handle(), "signed-on", handle,
                        PURPLE_CALLBACK(account_signed_on_cb), NULL);

  // Do the same on the already connected accounts
  // GList *connections = purple_connections_get_all();
  return TRUE;
}

gboolean otrng_prekey_plugin_unload(PurplePlugin *handle) { return TRUE; }
