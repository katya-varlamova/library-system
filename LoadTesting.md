# Без балансировки

**$  ab -c 10 -n 5000 http://127.0.0.1:80/api/v2/swagger**

This is ApacheBench, Version 2.3 <$Revision: 1879490 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 500 requests
Completed 1000 requests
Completed 1500 requests
Completed 2000 requests
Completed 2500 requests
Completed 3000 requests
Completed 3500 requests
Completed 4000 requests
Completed 4500 requests
Completed 5000 requests
Finished 5000 requests


Server Software:        library_system
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /api/v2/swagger
Document Length:        1444 bytes

Concurrency Level:      10
Time taken for tests:   13.750 seconds
Complete requests:      5000
Failed requests:        0
Total transferred:      7825000 bytes
HTML transferred:       7220000 bytes
Requests per second:    363.65 [#/sec] (mean)
Time per request:       27.499 [ms] (mean)
Time per request:       2.750 [ms] (mean, across all concurrent requests)
Transfer rate:          555.77 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   13 414.7      0   13122
Processing:     0   14 414.8      1   13123
Waiting:        0   14 414.8      1   13123
Total:          0   27 586.3      1   13127

Percentage of the requests served within a certain time (ms)
  50%      1
  66%      1
  75%      1
  80%      1
  90%      2
  95%      2
  98%      2
  99%      3
 100%  13127 (longest request)

# С балансировкой

**$  ab -c 10 -n 5000 http://127.0.0.1:80/api/v2/swagger**

This is ApacheBench, Version 2.3 <$Revision: 1879490 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 500 requests
Completed 1000 requests
Completed 1500 requests
Completed 2000 requests
Completed 2500 requests
Completed 3000 requests
Completed 3500 requests
Completed 4000 requests
Completed 4500 requests
Completed 5000 requests
Finished 5000 requests


Server Software:        library_system
Server Hostname:        127.0.0.1
Server Port:            80

Document Path:          /api/v2/swagger
Document Length:        1444 bytes

Concurrency Level:      10
Time taken for tests:   0.608 seconds
Complete requests:      5000
Failed requests:        0
Total transferred:      7825000 bytes
HTML transferred:       7220000 bytes
Requests per second:    8221.44 [#/sec] (mean)
Time per request:       1.216 [ms] (mean)
Time per request:       0.122 [ms] (mean, across all concurrent requests)
Transfer rate:          12564.99 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       1
Processing:     1    1   0.2      1       4
Waiting:        0    1   0.2      1       4
Total:          1    1   0.2      1       4

Percentage of the requests served within a certain time (ms)
  50%      1
  66%      1
  75%      1
  80%      1
  90%      1
  95%      2
  98%      2
  99%      2
 100%      4 (longest request)

# Доказательство работы балансировки

**$  ab -c 10 -n 10 http://127.0.0.1:80/api/v2/swagger**

[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8000: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.001 msec 1664751619.767 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8000: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.000 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8000: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.000 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8001: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.000 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8000: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.000 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8001: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.000 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8000: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.001 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8001: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.001 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8002: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.001 msec 1664751619.769 request_time 0.001
[03/Oct/2022:02:00:19 +0300] 127.0.0.1 - library_system - - -  127.0.0.1 to: 127.0.0.1:8002: GET /api/v2/swagger HTTP/1.0 200 upstream_response_time 0.001 msec 1664751619.769 request_time 0.001