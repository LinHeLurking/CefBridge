1. Long message (such as frame buffer) is transferred by OS dependent inter-process memory sharing mechanism.
2. Short message is sent with JNI, using string with `&&` separated key-value pairs.