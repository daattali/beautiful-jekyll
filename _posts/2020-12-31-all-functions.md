---
layout: post
title: Extracting all the functions from a Node/Express project
tags: [tech]
---
I wanted to extract all the functions from a Node.js project for documentation and testing reasons. 
I first thought that it would be a simple search / awk / grep task, however due to the many ways in which 
Node functions can be written (arrow), it was going to be harder than I expected.

Tried using awk with regexes:
```
awk '/.*function.*/ {print $0}' all_files.txt > all_functions.txt
awk '/const .* = .* =>/ {print $0}' all_files.txt >> all_functions.txt
```
But there were many false positives.

The internet recommended using a parser. So I found `esprima` and tried it out. To my horror, this parser does
not support the spread operator, which we use heavily in our code. So that was a deal-breaker.
```javascript
find ./ -name '*.js' > all_file_names.txt -> on terminal to create list of all js files
let allFileNames = fs.readFileSync('./all_file_names.txt', 'utf8');
const allFileNameList = allFileNames.split('\n');
allFileNameList.forEach(fileName => {
    try {
        console.log(fileName);
        let file = fs.readFileSync(fileName, 'utf8');
        file = file.replace(/\.\.\./g, '');
        let functionArg = esprima.parseScript(file);
        functionArg.body.forEach(el => {
            let variableDeclarator = el.declarations && Array.isArray(el.declarations) && el.declarations[0]
            let params = [];
            if (variableDeclarator && variableDeclarator.init && variableDeclarator.init.params) {
                variableDeclarator.init.params.forEach(arg => {
                    params.push(arg.name)
                });
                console.log(variableDeclarator.id.name, ' : ', [params.join()]);
            }
        });
    } catch (e) {
        console.log(`Unable to parse ${fileName}, ${JSON.stringify(e)}`);
    }
})
```

Tried out another, apparently simpler parser `acorn` using the files list I had created earlier. This definitely worked better than 
before, but I had to go through the result and backtrack my way to handling objects and assignments in the functions.
```javascript
const fs = require('fs');
const {Parser} = require('acorn');
const _ = require('lodash');
const MyParser = Parser.extend();
let allFileNames = fs.readFileSync('./all_file_names.txt', 'utf8');
const allFileNameList = allFileNames.split('\n');
const allFunctionsObj = {};
allFileNameList.forEach(fileName => {
    try {
        if (fileName) {
            let file = fs.readFileSync(fileName, 'utf8');
            const temp = MyParser.parse(file);
            const body = temp.body;
            const functionData = _.filter(body, (node) => node.type === 'FunctionDeclaration');
            _.map(functionData, (fnction) => {
                allFunctionsObj[fnction.id.name] = _.map(fnction.params, (param) => {
                    if (param.name) return param.name;
                    if (param.type === 'ObjectPattern') {
                        return _.map(param.properties, (prop) => prop.key.name);
                    }
                    if (param.type === 'AssignmentPattern') {
                        return param.left.name;
                    }
                });
            });
        }
    } catch (e) {
        console.log(e, 'error', fileName);
    }
});

console.log(allFunctionsObj);
fs.writeFile('./all_functions.json', JSON.stringify(allFunctionsObj), { flag: 'w' }, (res) => {
    console.log(res, 'done with write file');
});
```

Now I have a working script to parse out the functions in my code into a well-structured JSON that I can use for testing!
