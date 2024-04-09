pipeline {
    agent any
    stages {
        stage('ls') {
            steps {
                sh 'ls'
            }
        }
                stage('Grype/Syft Scan') {
            steps {
                // Run Grype scan
                sh 'grype -o json > grype-results.json'
                // Display the scan results
                sh 'cat grype-results.json'
            }
        }

       
    }
}


