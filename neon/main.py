import numpy as np
import matplotlib.pyplot as plt
import cv2
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook
from matplotlib.path import Path
from matplotlib.patches import Rectangle
import matplotlib as mpl
import sys


def plot_camera_distortion(u, v, ud, vd, sw, sh):
    margin = 0.1 * sw
    plt.figure(figsize=1.5 * mpl.figure.figaspect(sh / sw))
    plt.xlim(-margin, sw + margin)
    plt.ylim(-margin, sh + margin)
    plt.gca().invert_yaxis()
    plt.gca().xaxis.tick_top()
    plt.gca().add_patch(mpl.patches.Rectangle((0, 0), sw, sh, alpha=1,
                                              fill=False, linewidth=0.5,
                                              edgecolor='xkcd:grass green'))
    plt.plot(u, v, marker='.', linestyle='none', markersize='2',
             color='xkcd:light grey')
    plt.plot(ud, vd, marker='.', linestyle='none', markersize='2',
             color='xkcd:scarlet')


def checkerboard_image(width, height):
    grid_w = 16
    grid_h = 12
    patch_size = 30
    width = grid_w * patch_size
    height = grid_h * patch_size
    grid = np.array([[1, 0]*grid_w, [0, 1]*grid_w]*grid_h)
    patch = np.ones((patch_size, patch_size))
    img = np.kron(grid, patch)
    return img


def test1():
    checkerboard_image(0, 0)


def test():
    # sensor dimensions in px
    sw = 480
    sh = 360
    aspect = sh/sw
    fov = 85
    rr = np.tan(np.radians(fov/2))
    wby2 = rr * np.cos(np.arctan(aspect))
    hby2 = rr * np.sin(np.arctan(aspect))
    print('r =', rr)
    N = 31
    h_fov = 2 * np.degrees(np.arctan(wby2))
    v_fov = 2 * np.degrees(np.arctan(hby2))
    print('fov={}, hfov={}, vfov={}'.format(fov, h_fov, v_fov))
    xmin = -wby2
    xmax = wby2
    ymin = -hby2
    ymax = hby2
    xx = np.linspace(xmin, xmax, N)
    yy = np.linspace(ymin, ymax, N)

    x, y = np.meshgrid(xx, yy)
    x = x.ravel()
    y = y.ravel()

    r = np.sqrt(x**2 + y**2)

    # intrinsic parameters
    # focal lengths in px for full fov
    fx = fy = (np.hypot(sw, sh) / 2) / rr
    print('fl={}'.format(fx))
    # skew factor
    s = 0
    # principal point (px)
    cx = sw/2
    cy = sh/2
    # distortion parameters
    k1 = -0.1
    k2 = 0.05
    # Camera matrix
    K = np.array([[fx, s, cx], [0, fy, cy], [0, 0, 1]])

    # undistorted homogenous coords
    hp = np.vstack([x, y, np.ones(x.shape)])
    hp_i = np.matmul(K, hp)
    u = hp_i[0]
    v = hp_i[1]

    # distorted homogenous coords
    dist_factor = (1 + k1 * r**2 + k2 * r**4)
    xd = x * dist_factor
    yd = y * dist_factor
    hpd = np.vstack([xd, yd, np.ones(xd.shape)])
    hpd_i = np.matmul(K, hpd)
    ud = hpd_i[0]
    vd = hpd_i[1]

    # plot
    plot_camera_distortion(u, v, ud, vd, sw, sh)
    plt.show()


def test1():
    x = np.linspace(0, 10, 1000)
    y = np.sin(x)
    plt.plot(x, y)
    plt.show()


if __name__ == "__main__":
    test()
