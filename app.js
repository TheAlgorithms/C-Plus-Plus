let steps =[]
let currStep =0;
let playtime = null

function recordStep(arr,dp, i,j,msg){
    steps.push({
        array : [...arr],
        dp : [...dp],
        highlight : [i,j],
        message : msg
    });
}

function LISLogic(arr){
    steps = []
    currStep =0;

    const n = arr.length;
    let dp = Array(n).fill(1);
    let parent = Array(n).fill(-1);

    for(let i=0;i<n;i++){
        for(let j=0;j<i;j++){
            recordStep(arr,dp,i,j,`checking ${arr[j]} < ${arr[i]}`);

            if(arr[j]<arr[i] && dp[j]+1 > dp[i]){
                dp[i] = dp[j]+1;
                parent[i] = j;
                recordStep(arr,dp,i,j,`updating dp[${i}] = dp[${j}]`);
            }
        }
    }
    return {steps,dp,parent};
}

function displayResult(dp,parent,arr){
    let n = dp.length;
    let maxLen=0,lastIdx = -1;

    for(let i=0;i<n;i++){
        if(dp[i]>maxLen){
            maxLen = dp[i];
            lastIdx = i;
        }
    }
    let res=[];
    while(lastIdx !== -1){
        res.push(arr[lastIdx]);
        lastIdx = parent[lastIdx];
    }
    return res.reverse();
}

function nextStep(){
    if(currStep < steps.length-1)
        currStep++;
    return steps[currStep];
}

function prevStep(){
    if(currStep>0)
        currStep--;
    return steps[currStep];
}

function playSteps(onFrame, dp, parent, arr){
    if(playtime)    return;
    playtime = setInterval(()=>{
        if(currStep >= steps.length-1){
            clearInterval(playTimer);
            playtime = null;
            const final = displayResult(dp,parent,arr);
            const temp = document.getElementById("lisResult");
            if(temp){
                temp.textContent = "LIS Subsequence: " + final.join(" ");
                temp.classList.remove("hidden");
            }
            return;
        }
        // if(playtime)    return;
        currStep++;
        onFrame(steps[currStep]);
    },600);

}

function stopPlay(){
    clearInterval(playtime);
    playtime = null;
}
function resetStep(){
    currStep =0;
    return steps[currStep];
}

export const LISVisualizer = {
    LISLogic,nextStep,prevStep,playSteps,stopPlay,resetStep,
};
export {displayResult};