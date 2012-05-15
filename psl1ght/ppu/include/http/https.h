#ifndef __HTTPS_H__
#define __HTTPS_H__


#include <http/http.h>
#include <ssl/ssl.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * structures
 */

typedef struct _https_data
{
  char *ptr ATTRIBUTE_PRXPTR;
  size_t size;
} httpsData;


/*
 * callbacks
 */

typedef int (*httpsSslCallback)(s32 verErr,sslCert const sslCerts[],int certNum,const char *host,httpSslId id,void *arg);


/*
 * functions
 */

/* initialization */
s32 httpsInit(size_t caCertNum,const httpsData *caList);
s32 httpsEnd(void);

/* SSL certificate */
s32 httpsClientSetSslClientCertificate(httpClientId cid,const httpsData *cert,const httpsData *privKey);

/* SSL callback */
s32 httpsClientSetSslCallback(httpClientId cid,httpsSslCallback cb,void *arg);


#ifdef __cplusplus
	}
#endif

#endif

