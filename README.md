# web-server
  A webserver that supports  `htpp/1.1`.
  ##### the main idea:
- It handles multi clients request and respond correspondingly to their needs.
- without the use of multithreading we achieved to manage multi clients only by using epoll futures where the kernel waits until any interesting events occurs to trigger a wake up event to the user in order to handle that recieved or ready to send request/response.
- Each received request must be parsed for any syntax errors, unkown headers, or any miss implementation of rfc9110 standards, if so, responding with the corresponding error code based on rfc OFC.
  


## References
  - Rules to know before reading an rfc → https://www.rfc-editor.org/rfc/inline-errata/rfc2119.html
  - http Semantics → https://datatracker.ietf.org/doc/html/rfc9110
