#include <stdio.h>

#include <curl/curl.h>

int conecta_receita()
{
  CURL *curl;
  CURLcode res;
  FILE *headerfile;
  

  


  headerfile = fopen("dumpit", "w+");

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://homologacao.nfe2.fazenda.pr.gov.br/nfe/NFeRecepcao2?wsdl");
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, headerfile);
    while(1){
      curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
      
					//		if(pPassphrase)
    //  curl_easy_setopt(curl,CURLOPT_SSLCERTPASSWD,pPassphrase);
				/*		curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURL_SSLVERSION_SSLv3);
						curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
						  curl_easy_setopt(curl,CURLOPT_SSLKEY,"pvkey.pem");  						
						curl_easy_setopt(curl,CURLOPT_KEYPASSWD,"dirsicaf");curl_easy_setopt(curl,CURLOPT_CAINFO,"cacert.cer"); curl_easy_perform(curl);
      curl_easy_setopt(curl,CURLOPT_SSLCERT,"pubcert.pem");*/
					//	curl_easy_setopt(curl, CURLOPT_CAPATH, "./"); 
     // curl_easy_setopt(curl,CURLOPT_CAINFO,"cacert.pem");
      //curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,1L);
		/*				curl_easy_setopt(curl, CURLOPT_URL, "https://homologacao.nfe2.fazenda.pr.gov.br/nfe/NFeRecepcao2?wsdl");
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.28.0");
  curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
		//curl_easy_setopt(curl, CURLOPT_USERPWD, "dirsicaf");
  
		//curl_easy_setopt(curl, CURLOPT_KRBLEVEL, "clear");
  //curl_easy_setopt(curl, CURLOPT_TLSAUTH_PASSWORD,"dirsicaf");
		
		curl_easy_setopt(curl,CURLOPT_SSLKEY,"cert2013.pem");curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "dirsicaf");
	curl_easy_setopt(curl,CURLOPT_SSLCERT,"cacert.cer");
		curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"DER");//curl_easy_setopt(curl,CURLOPT_PASSWORD,"dirsicaf");
		
// curl_easy_setopt(curl, CURLOPT_CAINFO, "ca.pem");
		
  //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
  curl_easy_setopt(curl, CURLOPT_SSLVERSION, (long)CURL_SSLVERSION_SSLv3);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);*/
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	//	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		 curl_easy_setopt(curl, CURLOPT_URL, "https://homologacao.nfe2.fazenda.pr.gov.br/nfe/NFeRecepcao2?wsdl");
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.28.0");
  curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
  char key[]="key.pem",cert[]="client.pem"; 
		curl_easy_setopt(curl,CURLOPT_SSLKEY,key);curl_easy_setopt(curl,CURLOPT_SSLKEYTYPE,"PEM");curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "dirsicaf");
		curl_easy_setopt(curl,CURLOPT_SSLCERT,cert);curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
		curl_easy_setopt(curl,CURLOPT_SSLCERTPASSWD,"dirsicaf");
		curl_easy_setopt(curl, CURLOPT_CAINFO, "ca.pem");
  
  curl_easy_setopt(curl, CURLOPT_SSLVERSION, (long)CURL_SSLVERSION_SSLv3);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
					
      res = curl_easy_perform(curl);
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

      break;                   /* we are done... */
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
 fclose(headerfile);
  return 0;
}
