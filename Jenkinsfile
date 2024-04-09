pipeline {
    agent any
    stages {
        stage('Semgrep Scan') {
            steps {
                // Run Semgrep scan
                sh 'semgrep --config=p/r/python.flask --json . > semgrep-results.json'
                // Display the scan results
                sh 'cat semgrep-results.json'
            }
        }
        stage('Grype/Syft Scan') {
            steps {
                // Run Grype scan
                sh 'grype -o json > grype-results.json'
                // Run Syft scan
                sh 'syft -o json . > syft-results.json'
                // Display the scan results
                sh 'cat grype-results.json'
                sh 'cat syft-results.json'
            }
        }
        stage('GitLeaks Scan') {
            steps {
                // Run GitLeaks scan
                sh 'gitleaks --path . --report=gitleaks-results.json'
                // Display the scan results
                sh 'cat gitleaks-results.json'
            }
        }
        stage('Trivy Scan') {
            steps {
                // Run Trivy scan
                sh 'trivy --quiet --format json --output trivy-results.json .'
                // Display the scan results
                sh 'cat trivy-results.json'
            }
        }
        stage('KICS Scan') {
            steps {
                // Run KICS scan
                sh 'kics scan --output-path kics-results.json'
                // Display the scan results
                sh 'cat kics-results.json'
            }
        }
        // Add more stages for your build, test, and deploy steps as needed
        // ...
        stage('Cleanup') {
            steps {
                // Remove the scan results files
                sh 'rm semgrep-results.json'
                sh 'rm grype-results.json'
                sh 'rm syft-results.json'
                sh 'rm gitleaks-results.json'
                sh 'rm trivy-results.json'
                sh 'rm kics-results.json'
            }
        }
    }
}
==============================================
stages:
  - scan
  - cleanup
variables:
  SEMGREP_RESULTS_FILE: "semgrep-results.json"
  GRYPE_RESULTS_FILE: "grype-results.json"
  SYFT_RESULTS_FILE: "syft-results.json"
  GITLEAKS_RESULTS_FILE: "gitleaks-results.json"
  TRIVY_RESULTS_FILE: "trivy-results.json"
  KICS_RESULTS_FILE: "kics-results.json"
scan:
  stage: scan
  image: dev-sec-ops
  script:
    - semgrep --config=p/r/python.flask --json . > $SEMGREP_RESULTS_FILE
    - cat $SEMGREP_RESULTS_FILE
    - grype -o json > $GRYPE_RESULTS_FILE
    - syft -o json . > $SYFT_RESULTS_FILE
    - cat $GRYPE_RESULTS_FILE
    - cat $SYFT_RESULTS_FILE
    - gitleaks --path . --report=$GITLEAKS_RESULTS_FILE
    - cat $GITLEAKS_RESULTS_FILE
    - trivy --quiet --format json --output $TRIVY_RESULTS_FILE .
    - cat $TRIVY_RESULTS_FILE
    - kics scan --output-path $KICS_RESULTS_FILE
    - cat $KICS_RESULTS_FILE
cleanup:
  stage: cleanup
  image: alpine:latest
  script:
    - rm $SEMGREP_RESULTS_FILE
    - rm $GRYPE_RESULTS_FILE
    - rm $SYFT_RESULTS_FILE
    - rm $GITLEAKS_RESULTS_FILE
    - rm $TRIVY_RESULTS_FILE
    - rm $KICS_RESULTS_FILE
# Add more stages for your build, test, and deploy steps as needed
# ...
