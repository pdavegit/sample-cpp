pipeline {
    agent none
    stages {
       stage('build-ubuntu') {
          agent { 
          //    dockerfile {
	  //        filename 'Dockerfile-alpine-cpp-app.build'
	  //    }
	     docker { image 'prashantdave/ubuntu-cpp-env:18.04' }
          }      
          steps {
                sh 'make -f Makefile.ubuntu'
            }
        }
        //stage('build-ubuntu') {
        //   agent { 
        //      dockerfile {
	//          filename 'Dockerfile-ubuntu-cpp-app.build'
	//      }
        //  }      
        //  steps {
        //        sh 'make -f Makefile.ubuntu'
        //    }
        //}	
    }
}
