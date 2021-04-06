process.stdin.resume();
process.stdin.setEncoding('utf8');

let data = "";

process.stdin.on('data', function(chunk) {
    data += chunk.toString();
});

process.stdin.on('end', function() {
    runTestCases();
});

function runTestCases() {
    let lines = data.split("\n");
    const t = parseInt(lines.shift());
    for(let i=0; i<t; i++) {
        const params = lines.shift().split(" ").map(numberMapper);
        const queries = params[1];
        const arr = params[0];
        const nums = lines.shift().split(" ").map(numberMapper).slice(0, arr);
        
        for(let j=0; j<queries; j++) {
          const querybounds = lines.shift().split(" ").map(numberMapper);
          const sum = nums.slice(querybounds[0]-1, querybounds[1]).reduce((p,c,i) => p + (c^i), 0);
          console.log(sum);
        }
    }
}

function numberMapper(str) {
    return parseInt(str);
}