pipeline {
    agent none
    stages {
       stage('build') {
          agent { 
              dockerfile {
	          filename 'Dockerfile.alpine.build'
	      }
          }      
          steps {
                sh 'make -f Makefile.alpine'
            }
        }
    }
}
