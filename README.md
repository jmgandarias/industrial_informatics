# Indsutrial Informatics

Teaching material for [the Industrial Informatics course](https://jmgandarias.github.io/industrial_informatics), last year B.S. in Electronic Engineering at [the University of Málaga](https://www.uma.es)

Developed by [Juan M. Gandarias](https://jmgandarias.github.io/)

## Create your own material website

If you want to create your own website, you need to do the following:

1. Clone/fork [the repo](https://github.com/jmgandarias/industrial_informatics)
2. Install mkdocs and the required plugins

```bash
pip install mkdocs
pip install mkdocs-material
pip install mkdocs-awesome-pages-plugin
pip install mkdocs-git-revision-date-localized-plugin
pip install mkdocs-redirects
pip install mkdocs-video
```

> [!WARNING]  
> If you want to install it in WSL, you'll probably receive a <span style="color:orange">**_WARNING_**</span> displaying that the directory `YOUR_USER_DIRECTORY/.local/bin` is not included in the PATH. 
> If this happen, you won't be able to run mkdocs serve to see the changes locally. To solve that, you need to modify your `.bashrc` file as follows
>  ```bash
> cd ~/
> sudo gedit .bashrc
> ```
> Add the following line to the end of the file:
> `export PATH="YOUR_USER_DIRECTORY/.local/bin:$PATH"`

3. See the changes locally
   
```bash
mkdocs serve
```
