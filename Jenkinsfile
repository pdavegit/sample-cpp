pipeline {
    agent none
    stages {
       stage('build') {
          agent { 
              docker { 
              registryUrl 'https://index.docker.io/v1/'
              image 'ubuntu:18.04'
              } 
          }      
          steps {
                sh 'make'
            }
        }
    }
}
