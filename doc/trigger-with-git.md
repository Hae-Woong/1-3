# Trigger-with-Git

## Clone-the-repo

If you want to try the CI-Pipeline, first you have to clone the repo and create your own branch.
(For this you need the git cmdline tool <https://git-scm.com/downloads>)

1. Install git cmd tool.

    Set the proxy if needed. For example if you are behind a corporate proxy.

```powershell
git config --global http.proxy [http://proxyUsername:proxyPassword@proxy.server.com:port]
```

2. Generate SSH key.
Follow the instructions here:
1) https://docs.github.com/en/authentication/connecting-to-github-with-ssh/checking-for-existing-ssh-keys
2) https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
3) https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account

3. Clone the repo with ssh.
  Ex: git clone "git@github1.vg.vector.int:pnd/vecs-1-3-hil.git"

4. CD into the folder.
  Ex; cd .\vecs-1-3-hil\

5. Create your own branch.

git branch [BRANCH_NAME]
git checkout [BRANCH_NAME]


## Push-and-trigger

1. Make changes and commit the changes

Ex: Set the LightCtrl_SWC_P.LightIntensityToOff_Value to value 55 in .\ECU\BFC\Appl\LightCtrl.c to trigger a test fail.

git add [PATH_TO_CHANGED_FILES]
git commit 
git push --set-upstream origin [BRANCH_NAME]


2. After the first push, you can use:

```powershell
git add [PATH_TO_CHANGED_FILES]
git commit 
git push
```

3. Go to the Actions tab on Github to view the workflow runs.
