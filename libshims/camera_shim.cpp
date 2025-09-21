#include <media/stagefright/MediaMuxer.h>
#include <fcntl.h>
#include <cutils/log.h> // Para ALOGE
#include <jni.h>

extern "C" {


    void _ZN7android10MediaMuxerC1EiNS0_12OutputFormatE(int fd, android::MediaMuxer::OutputFormat format) {

        new android::MediaMuxer(fd, format);
        ALOGD("shim: MediaMuxer constructor shimmed.");
    }

    int jniGetFDFromFileDescriptor(JNIEnv* env, jobject fileDescriptor) {
        if (!fileDescriptor) {
            ALOGE("shim: jniGetFDFromFileDescriptor received null FileDescriptor.");
            return -1;
        }

        static jclass fdClass = env->FindClass("java/io/FileDescriptor");
        if (fdClass == NULL) {
            ALOGE("shim: Failed to find class java/io/FileDescriptor");
            return -1;
        }

        static jfieldID fdField = env->GetFieldID(fdClass, "descriptor", "I");
        if (fdField == NULL) {
            ALOGE("shim: Failed to find field 'descriptor' in FileDescriptor");
            return -1;
        }

        return env->GetIntField(fileDescriptor, fdField);
    }

}
