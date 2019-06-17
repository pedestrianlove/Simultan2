build:
	cp Fira* /Library/Fonts/
	open Pro.terminal
	cp makefile_bak ~/makefile

zsh:
	brew install zsh
	brew install exa
	brew tap sambadevi/powerlevel9k
	brew install powerlevel9k
	echo "source /usr/local/opt/powerlevel9k/powerlevel9k.zsh-theme" >> ~/.zshrc
	exec zsh	
