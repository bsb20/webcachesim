all:
	clang++ -I./ -std=c++11 -stdlib=libc++ request_rand_stream.cpp request_filestream.cpp event.cpp machine.cpp event_queue.cpp main.cpp -o cache

debug:
	clang++ -I./ -std=c++11 -stdlib=libc++ request_stream.cpp event.cpp machine.cpp main.cpp -o cache -g

test:
	./cache test.trace 0 LRU 1
