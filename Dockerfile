#INSTALL UBUNTU AND BASICS#################################
FROM ubuntu:22.04

RUN apt -y update && apt-get install -y cmake build-essential git g++ autotools-dev gdb pkg-config valgrind

###########################################################

#INSTALL GTK4##############################################

RUN apt-get install -y libgtkmm-3.0-dev  libgtkmm-3.0-doc  mm-common  libgtk-4-bin libgtk-4-common libgtk-4-dev libgtk-4-doc libxml-sax-expatxs-perl xsltproc iputils-ping

WORKDIR /app

COPY ./3rdparty ./3rdparty

#INSTALL LIBSIG - Signal and Callbacks library

RUN cd /app/3rdparty/GTKmm-4.6; tar Jxvf libsigc++-3.0.7.tar.xz; 
RUN cd /app/3rdparty/GTKmm-4.6/libsigc++-3.0.7; ./autogen.sh --prefix=/usr/local;
RUN cd /app/3rdparty/GTKmm-4.6/libsigc++-3.0.7; make -j6; 
RUN cd /app/3rdparty/GTKmm-4.6/libsigc++-3.0.7; make install;

# #INSTALL GLIBMM - General propouse library for GTK

RUN cd /app/3rdparty/GTKmm-4.6; tar Jxvf glibmm-2.68.2.tar.xz; 
RUN cd /app/3rdparty/GTKmm-4.6/glibmm-2.68.2; ./autogen.sh --prefix=/usr;
RUN cd /app/3rdparty/GTKmm-4.6/glibmm-2.68.2; make -j6; make install;

# #INSTALL CAIROMM - 2D Graphics library

RUN cd /app/3rdparty/GTKmm-4.6; tar Jxvf cairomm.tar.xz; 
RUN cd /app/3rdparty/GTKmm-4.6/cairomm; ./autogen.sh --prefix=/usr;
RUN cd /app/3rdparty/GTKmm-4.6/cairomm; make -j6; make install;

# #INSTALL PANGOMM - Laying out and redering text

RUN cd /app/3rdparty/GTKmm-4.6; tar Jxvf pangomm-2.50.0.tar.xz; 
RUN cd /app/3rdparty/GTKmm-4.6/pangomm-2.50.0; ./autogen.sh --prefix=/usr;
RUN cd /app/3rdparty/GTKmm-4.6/pangomm-2.50.0; make -j6; make install;

#INSTALL GTKmm4.6 - UI Library

RUN cd /app/3rdparty/GTKmm-4.6; tar Jxvf gtkmm-4.6.1.tar.xz; 
RUN cd /app/3rdparty/GTKmm-4.6/gtkmm-4.6.1; ./autogen.sh --prefix=/usr;
RUN cd /app/3rdparty/GTKmm-4.6/gtkmm-4.6.1; make -j6; make install;

###########################################################

#INSTALL CYCLONEDDS########################################

#INSTALL ECLIPSE CYCLONE DDS

RUN cd /app/3rdparty/cyclonedds-0.10.4; tar -xvf cyclonedds-0.10.4.tar.gz; 
RUN cd /app/3rdparty/cyclonedds-0.10.4/cyclonedds-0.10.4; mkdir build; cd build; cmake -DCMAKE_INSTALL_PREFIX=/app/3rdparty/cyclonedds-0.10.4/cyclonedds-0.10.4 -DBUILD_EXAMPLES=ON ..
RUN cd /app/3rdparty/cyclonedds-0.10.4/cyclonedds-0.10.4/build; cmake --build . ; cmake --build . --target install

#INSTALL CYCLONE DDS C++

RUN cd /app/3rdparty/cyclonedds-0.10.4; tar -xvf cyclonedds-cxx-0.10.4.tar.gz; 
RUN cd /app/3rdparty/cyclonedds-0.10.4/cyclonedds-cxx-0.10.4; mkdir build; cd build; cmake -DCMAKE_INSTALL_PREFIX=/app/3rdparty/cyclonedds-0.10.4/cyclonedds-cxx-0.10.4 -DCMAKE_PREFIX_PATH=/app/3rdparty/cyclonedds-0.10.4/cyclonedds-0.10.4 -DBUILD_EXAMPLES=ON ..
RUN cd /app/3rdparty/cyclonedds-0.10.4/cyclonedds-cxx-0.10.4/build; cmake --build . ; cmake --build . --target install


###########################################################

#INSTALL VIDEO MEDIAX DRIVERS##############################

RUN apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-tools libgoogle-glog-dev libswscale-dev libgflags-dev swig python3 libpython3-all-dev

RUN cd /app/3rdparty/mediaX-0.8.2; tar Jxvf MediaX-0.8.2.tar.xz; 
RUN cd /app/3rdparty/mediaX-0.8.2/MediaX-0.8.2; mkdir build; cd build; cmake -DBUILD_CUDA=OFF -DEXAMPLES=ON -DBUILD_TESTING=OFF -DGST_SUPPORTED=ON -DBUILD_QT6=OFF ..
RUN cd /app/3rdparty/mediaX-0.8.2/MediaX-0.8.2/build; cmake --build . -j6

###########################################################
