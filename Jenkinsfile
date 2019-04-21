pipeline {
    agent none
    stages {
       stage('build') {
          agent { 
	      docker { 
                  registryUrl 'https://index.docker.io/v1/'
              }
              dockerfile true
          }      
          steps {
                sh 'make'
            }
        }
    }
}
