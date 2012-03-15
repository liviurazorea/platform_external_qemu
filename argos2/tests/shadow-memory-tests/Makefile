all:
	gcc -Wall -O2 -g -fno-strict-aliasing -I. -I.. -I/home/liviur/android_prj/external/qemu/argos2/target-i386 -I/home/liviur/android_prj/external/qemu/argos2 -I/home/liviur/android_prj/external/qemu/argos2/i386-softmmu -MMD -MP -DNEED_CPU_H -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -I/home/liviur/android_prj/external/qemu/argos2/fpu -DHAS_AUDIO -DHAS_AUDIO_CHOICE -I/home/liviur/android_prj/external/qemu/argos2/slirp t1.c -o t1 -largos -L../../i386-softmmu

#all:
#	gcc -I../../target-i386 -I/home/liviur/android_prj/external/qemu/argos2/target-i386 -I/home/liviur/android_prj/external/qemu/argos2 -I/home/liviur/android_prj/external/qemu/argos2/i386-softmmu -I/home/liviur/android_prj/external/qemu/argos2/fpu t1.c -o t1 -largos -L../../i386-softmmu
