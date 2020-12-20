build:
	cp Fira* /Library/Fonts/
	open Pro.terminal
	cp makefile_bak ~/makefile

osx:
	brew install zsh
	brew install exa
	brew tap sambadevi/powerlevel9k
	brew install powerlevel9k
	cp zshrc_osx ~/.zshrc
	exec zsh

arch:
	sudo pacman -S zsh
	sudo pacman -S exa
	sudo pacman -S zsh-theme-powerlevel9k
	cp zshrc_linux ~/.zshrc
	exec zsh
ubuntu:
	git clone --branch release --depth 1 'https://github.com/adobe-fonts/source-code-pro.git' "~/adobe-fonts/source-code-pro"
	fc-cache -f -v "~/adobe-fonts/source-code-pro"
	sudo apt install konsole fonts-firacode zsh conky-all
	mkdir ~/.local/share/konsole/
	cp Dracula.colorscheme ~/.local/share/konsole/
	cp zshrc_ubuntu ~/.zshrc
	cp conkyrc ~/.conkyrc
	git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/powerlevel10k
	echo 'source ~/powerlevel10k/powerlevel10k.zsh-theme' >>~/.zshrc
