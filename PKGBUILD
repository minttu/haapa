_pkgname=haapa
pkgname=haapa-git
pkgver=0.1
pkgrel=1
pkgdesc='A simple status program in C'
url='http://github.com/JuhaniImberg/haapa'
license=('MIT')
arch=('i686' 'x86_64')
depends=('libevent')
makedepends=('git')
conflicts=('haapa')
provides=('haapa')
source=('git://github.com/JuhaniImberg/haapa')
md5sums=('SKIP')

pkgver() {
	cd $_pkgname
	git describe --always | sed -e 's|-|.|g'
}

build() {
	cd $_pkgname
	make
}

package() {
	cd $_pkgname
	make PREFIX=/usr DESTDIR="$pkgdir" install
}