![Nederlandse vlag](../images/nl.gif) Nederlands

[Navigate to English version](#English)

## Installeren

De volgende stappen zijn nodig om documentatie zoals deze site te realiseren in Github:

* Maak een account aan op github en bewaar gebruikersnaam en wachtwoord. Maak een eerste repository.
* Download git en installeer
* Download github-desktop en installeer
* Download Atom en installeer. Atom is niet nodig. Iedere testverwerker kun je gebruiken.
* Stel github-account en repository in op github-desktop
* Clone de directory naar je laptop

## Commit & push

Herhaal onderstaande stappen steeds weer als de documentatie moet worden bijgewerkt:

* Maak/wijzig of verwijder een bestand en/of mappen in de repository op je laptop
* Commit de wijzigingen in github-desktop door linksonder op de knop te drukken. Geef eventueel commentaar mee in het vakje daarboven. Links zie je alle wijzigingen aan bestanden. Door op een bestand te klikken zie je zelfs de wijzigingen binnen de bestanden (indien mogelijk).

![Commit](./images/githubdesktop_commit.PNG)

* Push de wijzigingen naar github. De wijzigingen zijn nu zichtbaar voor de hele wereld.

![Push](./images/githubdesktop_push.PNG)

👍 Je kunt meteen kijken hoe het er uit ziet door de preview Markdown aan te zetten met b.v. Ctrl+Shift+M (grappig [Markdown emoji](https://www.webfx.com/tools/emoji-cheat-sheet/) zie je **niet** in preview na standaard installatie. Daarvoor moet je extra Atom package installeren [zie](../Softwaretooling.md))

![AtomPreview](./images/AtomPreview.png)

## Pull

Als er wijzigingen worden uitgevoerd op de Github-server b.v. via een browser en deze wijzigingen worden ge-commit, zie je in de github-desktop het volgende:

![githubdesktopremotechange](./images/githubdesktopremotechange.PNG)

* Druk op Pull Origin om de wijzigingen ook op je lokale git-repository door te voeren

## Conflicten

Conflicten zijn zeldzaam als je de enige gebruiker bent, die altijd vanuit de laptop commit & pushed naar de github-server. Als er meerdere gebruikers zijn of je om wat voor reden dan ook toch op de server aan de slag gaat, kun je conflicten krijgen.

* Stel je wijzigt in dit document github-desktop in github-desktAp:

![githubdesktopconflict1](./images/githubdesktopconflict1.PNG)

* Maar bijna tegelijkertijd direct op github via een browser in github-desktEp.

![githubdesktopconflict2](./images/githubdesktopconflict2.PNG)

Daarna wordt als eerste de github-server via de browser ge-commit. Als je daarna probeert github-desktop te comitten krijg je onderstaand scherm. Druk dan op Fetch:

![githubdesktopconflict3](./images/githubdesktopconflict3.PNG)

* Daarna volgt dit scherm. Druk op Pull Origin

![githubdesktopconflict4](./images/githubdesktopconflict4.PNG)

* Dan volgt de mededeling dat er een conflict is.

![githubdesktopconflict5](./images/githubdesktopconflict5.PNG)

* In je tekstverwerker zoals Atom verschijnt een extra stuk

![githubdesktopconflict6](./images/githubdesktopconflict6.PNG)

Bij <<<<<<HEAD staat jouw lokale tekst; bij ======= staat de tekst, die is ge-commit op de server. Neem de juiste beslissing wat correct is en wat niet; pas dit lokaal aan en commit opnieuw.


![English flag](../images/gb.gif) English

## Install

The next steps are neccessary te create documentation like this site:

* Create an account on github and save username and password. Create first repository.
* Download git and install
* Download github-desktop and install
* Download Atom and install. Any text editor can be used instead.
* Set your github-account and repository in github-desktop
* Clone the directory to your laptop

## Commit & push

Repeat the following steps eacht time tyhe documentation needs an update:

* Create/change/delete files and/or directories in the local repository
* Commit the changes by clicking down left. It's possible to add a comment to your commit. On the left you see all files. By clicking a file you can see (if possible) the changes made to that particular file on the right.

![Commit](./images/githubdesktop_commit.PNG)

* Push the changes to github. These changes are now available to the whole world.

![Push](./images/githubdesktop_push.PNG)

👍 You can see the result of your work immediately by switching on the preview of Markdown with Ctrl+Shift+M (funny [Markdown emoji](https://www.webfx.com/tools/emoji-cheat-sheet/) are **not** shown in the preview after standard installation. Add an extra Atom package  [see](../Softwaretooling.md))

![Preview](./images/AtomPreview.png)

## Pull

If you make only changes directly to the github server through a browser and commit them, you can see in github desktop that there were changes:

![githubdesktopremotechange](./images/githubdesktopremotechange.PNG)

* Push Pull Origin to put the remote changes into ypour local git-repository

## Conflicts

Conflicts are rare when you are the only user working on his laptop and committing & pushing to the github server. If there are more coworkers or you work both local and remote conflict can appear.

* Suppose in this document you change github-desktop in github-desktAp:

![githubdesktopconflict1](./images/githubdesktopconflict1.PNG)

* But at the same time in github server through a browser into github-desktEp.

![githubdesktopconflict2](./images/githubdesktopconflict2.PNG)

* Suppose you commit to github server first. Trying to commit in github desktop will lead to a conflict. Push Fetch:

![githubdesktopconflict3](./images/githubdesktopconflict3.PNG)

* The form below will appear. Push Pull Origin

![githubdesktopconflict4](./images/githubdesktopconflict4.PNG)

* Then there is a message about a conflict.

![githubdesktopconflict5](./images/githubdesktopconflict5.PNG)

* In your favorit editor like Atom an extra piece of text appears:

![githubdesktopconflict6](./images/githubdesktopconflict6.PNG)

At <<<<<<HEAD is your local text; at ======= is the text, committed on the server. Decide which text is correct and change. Then commit again.
