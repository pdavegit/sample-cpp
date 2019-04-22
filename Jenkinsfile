pipeline {
    agent none
    stages {
       stage('build-alpine') {
          agent { 
              dockerfile {
	          filename 'Dockerfile.alpine.build'
	      }
          }      
          steps {
                sh 'make -f Makefile.alpine'
            }
        }
        stage('build-ubuntu') {
           agent { 
              dockerfile {
	          filename 'Dockerfile.ubuntu.build'
	      }
          }      
          steps {
                sh 'make -f Makefile.ubuntu'
            }
        }	
    }
}
