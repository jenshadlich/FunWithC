#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_bucket(const char *uri, const char **bucket, int *bucket_len);
static int get_object_key(const char *uri, const char **object_key, int *object_key_len);

int main() {
	const char *uri = "PUT /bucket/obj/ect?foo=bar HTTP/1.1";

	const char *bucket_ptr = NULL;
	int bucket_len = 0;
	const char *object_key_ptr = NULL;
	int object_key_len = 0;

	get_bucket(uri, &bucket_ptr, &bucket_len);
	get_object_key(uri, &object_key_ptr, &object_key_len);

	char* bucket = malloc(bucket_len + 1);
	bucket[bucket_len] = '\0';
	memcpy(bucket, bucket_ptr, bucket_len);

	char* object_key = malloc(object_key_len + 1);
	object_key[object_key_len] = '\0';
	memcpy(object_key, object_key_ptr, object_key_len);

	printf("'%s' -> '%s':'%s'\n", uri, bucket, object_key);
	exit(0);
}

static int get_bucket(const char *uri, const char **bucket, int *bucket_len) {
	int slashes = 0;
	int start = 0;

	for (int i = 0; i < strlen(uri); i++) {
		if (uri[i] == '/') {
			if (slashes == 1) {
				*bucket_len = i - start;
				break;
			}
			slashes++;
		}
		if (slashes == 1 && start == 0) {
			start = i + 1;
			*bucket = uri + start;
		}
	}
 
	return 0;
}

static int get_object_key(const char *uri, const char **object_key, int *object_key_len) {
	int slashes = 0;
	int start = 0;

	for (int i = 0; i < strlen(uri); i++) {
		if (uri[i] == '/') {
			slashes++;
		}
		if ((slashes > 0 && uri[i] == ' ') || (uri[i] == '?')) {
			*object_key_len = i - start;
			break;
		}
		if (slashes == 2 && start == 0) {
			start = i + 1;
			*object_key = uri + start;
		}
	}
 
	return 0;
}