#include "handlers.h"
#include "../common/protocol.h"
#include "../common/trans_buffer.h"
#include "../common/vector.h"
#include "../common/utils.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

void* thread_routine(void* config) {
	int sockfd = ((struct thread_config*)config)->socket;

	int thread_connection_count = 0;

	while (1) {
		int client_socket = accept(sockfd, NULL, NULL);
		printf("New connection: fd:%d; count:%d\n", client_socket, ++thread_connection_count);
		handle_connection(client_socket);
	}
}

int handle_connection(int sockfd) {
	struct vector* buf = vector_init(1);
	struct trans_buffer* trans_buf = trans_buffer_init(sockfd);

	trans_buffer_read(trans_buf, buf);
	hexdump(buf->data, buf->length, 8);

	trans_buffer_read(trans_buf, buf);
	hexdump(buf->data, buf->length, 8);
	
	trans_buffer_read(trans_buf, buf);
	hexdump(buf->data, buf->length, 8);
	
	trans_buffer_read(trans_buf, buf);
	hexdump(buf->data, buf->length, 8);

	vector_free(buf);
	trans_buffer_free(trans_buf);
	return 0;
}