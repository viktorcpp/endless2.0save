module.exports = function(grunt) {
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        concat: {
            /*dist: {
				src: [
					'js/libs/*.js',
					'js/global.js'
				],
				dest: 'js/build/production.js',
			}//*/
        },
		sass: {
			/*dist: {
				options: {
					style: 'expanded',
					sourcemap: 'none'
				},
				files: {
					'css/main.css': 'scss/main.scss'
				}
			}//*/
		},
        compass: {
            clean: {
                options: {
                    clean: true
                }
            },
            dist: {
                options: {
                    httpPath: '../',
                    sassDir: 'scss',
                    cssDir: 'css',
                    imagesDir: 'images',
                    force: true,
                    environment: 'production'
                }
            },
            dev: {
                options: {
                    httpPath: '../',
                    sassDir: 'scss',
                    cssDir: 'css',
                    imagesDir: 'images',
                    force: false,
                    environment: 'development'
                }
            },
            compile: {
                options: {}
            }
        },
		watch: {
            options: {
                livereload: false
            },
            sass: {
                files: ['scss/**/*.scss'],
                tasks: ['compass:dev'],
                options: {
                    livereload: false
                }
            },
            scripts: {
                files: ['js/*.js']
            },
            css: {
                files: ['css/*.css']
            },
            templates: {
                files: ['**/*.php']
            }
		}
    });

    grunt.loadNpmTasks('grunt-contrib-compass');
    grunt.loadNpmTasks('grunt-contrib-watch');
    grunt.loadNpmTasks('grunt-newer');

    grunt.registerTask('default', ['compass', 'watch']);

};
