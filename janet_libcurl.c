#include <janet.h>
#include <stdio.h>
#include <curl/curl.h>

struct memory
{
  char *response;
  size_t size;
};

static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)userp;

  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if (ptr == NULL)
    return 0; /* out of memory! */

  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;

  return realsize;
}

struct memory chunk = {0};

int curl_easy(const char url[])
{
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return 0;
}

static Janet curl_easy_wrapped(int32_t argc, Janet *argv)
{
  janet_fixarity(argc, 1);

  const char *url = janet_getcstring(argv, 0);
  const char *ret = curl_easy(url);

  struct memory ret_chunk = chunk;
  chunk = (const struct memory){ 0 };

  return janet_cstringv(ret_chunk.response);
}

static const JanetReg janet_curl_easy_cfuns[] = {
    {"curl-easy", curl_easy_wrapped,
     "(curl-easy url)\n\n"
     "Makes an http/s request using default settings of curl\\_easy. "
     "Returns result of request."},
    {NULL, NULL, NULL}};

JANET_MODULE_ENTRY(JanetTable *env)
{
  janet_cfuns(env, "janet-libcurl", janet_curl_easy_cfuns);
};
