---
layout: page
title: Jest Error Parser
permalink: /tools/jest-error-viewer.md
description: Jest Error Parser
---

<div class="tool-body">
    <h1>Jest Error Parser</h1>

    <textarea id="jestError" placeholder="Paste Jest error string here..."></textarea>
    <button onclick="parseJestError()">Check Differences</button>

    <h2>Difference:</h2>
    <div class="output-container">
        <div class="expected-container">
            <h3>Expected:</h3>
            <pre id="expectedOutput" class="output"></pre>
        </div>
        <div class="received-container">
            <div class="received-header">
                <h3>Received:</h3>
                <button onclick="toggleDiff()">Toggle Diff</button>
            </div>
            <pre id="receivedOutput" class="output"></pre>
        </div>
    </div>

    <div class="diff-container">
        <h3>Diff:</h3>
        <div id="diffOutput" class="diff"></div>
    </div>
</div>

<script type="module">
    import JsonDiff from 'https://esm.sh/json-diff@1.0.6';
    import * as jsondiffpatch from 'https://esm.sh/jsondiffpatch@0.6.0';
    import * as annotatedFormatter from 'https://esm.sh/jsondiffpatch@0.6.0/formatters/annotated';
    import * as htmlFormatter from 'https://esm.sh/jsondiffpatch@0.6.0/formatters/html';

    window.settings = {
        showUnchanged: true
    };

    window.parseJestError = function parseJestError() {
        const jestError = document.getElementById('jestError').value;
        const dateRegex = /(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3}Z)/gu;

        const stringFix = jestError
            .replace(/Any<String>/gu, `"Any<String>"`)
            .replace(/Any<Date>/gu, `"Any<Date>"`)
            .replace(/\n/gu, '')
            .replace(/Expected: /gu, '')
            .replace(/ObjectContaining /gu, '')
            .replace(/ArrayContaining /gu, '')
            .replace(/undefined/gu, '"undefined"')
            .replace(dateRegex, '"$1"');

        // Divide into expected and received arrays
        let [expected, received] = stringFix.split('Received:');
        expected = `[${expected.trim()}]`;
        received = `[${received.trim()}]`;

        // Display the results
        document.getElementById('expectedOutput').textContent = JSON.stringify(JSON.parse(expected, null, 2), null, 2);
        document.getElementById('receivedOutput').innerHTML = getDiff(expected, received);
        // document.getElementById('receivedOutput').textContent = JSON.stringify(JSON.parse(received, null, 2), null, 2);

        // Use json-diff to show the differences
        showDiff(expected, received);
        // showDiffOld(expected, received);
    };

    window.toggleDiff = function toggleDiff() {
        if (window.settings.showUnchanged) {
            window.settings.showUnchanged = false;
            htmlFormatter.hideUnchanged();
        } else {
            window.settings.showUnchanged = true;
            htmlFormatter.showUnchanged();
        }
    };

    window.getDiff = function getDiff(expected, received) {
        try {
            const expectedJson = JSON.parse(expected, null, 2);
            const receivedJson = JSON.parse(received, null, 2);
            const diff = jsondiffpatch.diff;
            const differences = diff(expectedJson, receivedJson);

            return htmlFormatter.format(differences, expectedJson);
        } catch (error) {
            return 'Error parsing JSON: ' + error.message;
        }
    };

    window.showDiff = function showDiff(expected, received) {
        try {
            const expectedJson = JSON.parse(expected, null, 2);
            const receivedJson = JSON.parse(received, null, 2);

            const diff = jsondiffpatch.diff;
            const differences = diff(expectedJson, receivedJson);
            const diffOutput = document.getElementById('diffOutput');

            window.d = {
                expectedJson,
                receivedJson,
                differences
            };

            // Display the diff result
            diffOutput.innerHTML = htmlFormatter.format(differences, expectedJson);
        } catch (error) {
            document.getElementById('diffOutput').textContent = 'Error parsing JSON: ' + error.message;
        }
    };

    window.showDiffOld = function showDiffOld(expected, received) {
        try {
            const expectedJson = JSON.parse(expected);
            const receivedJson = JSON.parse(received);
            const diff = JsonDiff.diff(expectedJson, receivedJson);
            const diffOutput = document.getElementById('diffOutput');

            // Display the diff result
            diffOutput.textContent = JSON.stringify(diff, null, 2) || 'No differences';
        } catch (error) {
            document.getElementById('diffOutput').textContent = 'Error parsing JSON: ' + error.message;
        }
    }
</script>

<style>
    .tool-body {
        font-family: Arial, sans-serif;
        margin: 20px;
        padding: 20px;
        background-color: #f9f9f9;
        border: 1px solid #ddd;
        border-radius: 5px;
    }

    textarea {
        width: 100%;
        height: 150px;
        margin-bottom: 10px;
        padding: 10px;
        border: 1px solid #ccc;
        border-radius: 4px;
    }

    button {
        padding: 10px 15px;
        font-size: 16px;
        background-color: #007bff;
        color: white;
        border: none;
        border-radius: 4px;
        cursor: pointer;
    }

    button:hover {
        background-color: #0056b3;
    }

    .output-container {
        display: flex;
        justify-content: space-between;
        margin-top: 20px;
    }

    .output-container>div {
        flex: 1;
        width: 48vw;
        overflow: auto;
    }

    .received-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
    }

    .output {
        flex: 1;
        margin: 0 10px;
        padding: 10px;
        background-color: #eee;
        border-radius: 4px;
        overflow-x: auto;
    }

    .diff-container {
        display: none;
    }

    .diff {
        background-color: #ffeb3b;
        padding: 10px;
        border-radius: 4px;
        margin-top: 10px;
    }
</style>
