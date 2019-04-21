pipeline {
    agent none
    stages {
       stage('build') {
          agent { 
              dockerfile {
	          filename 'Dockerfile.alpine'
	      }
          }      
          steps {
                sh 'make'
            }
        }
    }
}
