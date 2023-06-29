# Publish changes

## Checkout (preferred!)
- Stash changes
- Go to <gerrit link>
- Refresh page
- Click download, copy checkout link (paste into terminal)
- git switch -c <local-branch-name> 
- git stash pop ('pop')
    - Fix merge conflicts
- git commit --amend 
    - Enter new commit message into editor
    - git push origin HEAD:refs/drafts/master (this creates a new patch in Gerrit)

### Checkout (with bash profile)
- 'co <id>'
- 'git switch -c <local-branch-name>' ('gsc <branch>')
- 'git stash pop' ('pop')
    - fix potential merge conflicts
- 'push' (includes add, commit, push)

## Cherrypick
- stage changes
- git commit --amend 
- Go to <gerrit link>
- Refresh page
- Click download, copy cherrypick link (paste into terminal)
    - Fix merge conflicts
    - git cherry-pick --continue
    - This results in 2 commits on the same change ID
    - git rebase -i HEAD~2 (usually 2 is enough)
    - Pick one, squash one, write new commit message
- git push origin HEAD:refs/drafts/master (this creates a new patch in Gerrit)

### Cherrypick (with bash profile)
- 'cp <id>' with id from link above
- rebase if necessary
- git cherry-pick --continue ('cpc')
- 'push'