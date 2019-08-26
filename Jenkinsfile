node('') {
    checkout scm
    stage('build-ubuntu') {
       sh 'docker pull prashantdave/ubuntu-cpp-env:18.04'    
        docker.withRegistry('https://index.docker.io/v1') {
            docker.image('prashantdave/ubuntu-cpp-env:18.04').inside {
                sh 'cd src && make -f Makefile.ubuntu all'
		sh 'cd src && make -f Makefile.ubuntu test'
            }
        }
    }
/*    stage('build-alpine') {
       sh 'docker pull prashantdave/alpine-cpp-env:latest'	
        docker.withRegistry('https://index.docker.io/v1') {
            docker.image('prashantdave/alpine-cpp-env:latest').inside {
                sh 'make -f Makefile.alpine all'
            }
        }
    }  */   
}
