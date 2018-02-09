from setuptools import setup, Extension


module = Extension(
    name='accounts',
    sources=['accounts/accountsmodule.c'],
    include_dirs=[],
    libraries=[],
    extra_objects=[],
    extra_compile_args=['-Wno-unused-function']
)

setup(
    name='accounts',
    author='Sergio Pulgarin',
    author_email='serpulga@gmail.com',
    packages=['accounts', 'accounts.tests'],
    package_dir={'accounts': 'lib', 'accounts.tests': 'tests'},
    version='0.0.1',
    description='Pycon Medellin 2018!',
    ext_modules=[module]
)
