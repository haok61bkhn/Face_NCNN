# Face_NCNN

#install ncnn

    https://github.com/Tencent/ncnn/wiki/how-to-build

# download model

    mkdir models

    cd models
  
  # model retina
  
     gdown https://drive.google.com/uc?id=1ClR2evj2II3MMfJz2PEAg5ulRDVeZGQS

     gdown https://drive.google.com/uc?id=10SGVApmn0rXNduRfYDRRIANaqa_svD36
   
  #model res18:
  
     gdown https://drive.google.com/uc?id=1SX3mODL_tdQKRjRzh1V4qmHmP6ZU1x5G

     gdown https://drive.google.com/uc?id=1-nb7DG4HCAYktJee2J4yuHLzzuCl0VbE
   
  # model res50  

     gdown https://drive.google.com/uc?id=1fs6__eFKetPim6_UMR4Xb3f0M2KJLdlU

     gdown https://drive.google.com/uc?id=1mWBg6LD0VHcjnpO0Jnmwp0VpU1N1IF5Q
   
 
 
 # install
 
    mkdir build

    cd build

    export ncnn_DIR=YOUR_NCNN_PATH/build/install/lib/cmake/ncnn

    cmake ..

    make

    ./facerecognition
  

   
    
