build:
	cp Fira* /Library/Fonts/
	open Pro.terminal
	cp makefile_bak ~/makefile

osx:
	brew install zsh
	brew install exa
	brew tap sambadevi/powerlevel9k
	brew install powerlevel9k
	echo "source /usr/local/opt/powerlevel9k/powerlevel9k.zsh-theme" >> ~/.zshrc
	cp zshrc_osx ~/.zshrc
	exec zsh

arch:
	sudo pacman -S zsh
	sudo pacman -S exa
	sudo pacman -S zsh-theme-powerlevel9k
	echo "/usr/share/zsh-theme-powerlevel9k/powerlevel9k.zsh-theme" >> ~/.zshrc
	cp zshrc_linux ~/.zshrc
	exec zsh	
