using System;
using System.Collections;
using System.Windows;
using System.Windows.Controls;
using WineDemoUserControls.ViewModel;

namespace WineDemoUserControls
{
    public partial class WineList : UserControl
    {
        public WineList()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty ProductsProperty =
            DependencyProperty.Register(
                "Products",
                typeof(IEnumerable),
                typeof(WineList),
                new PropertyMetadata(null, OnProductsPropertyChangedStatic));

        public IEnumerable Products
        {
            get { return (IEnumerable)GetValue(ProductsProperty); }
            set { SetValue(ProductsProperty, value); }
        }

        private static void OnProductsPropertyChangedStatic(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            WineList wineList = d as WineList;
            if (wineList != null) {
                wineList.OnProductsPropertyChangedInstance(e);
            }
        }

        private void OnProductsPropertyChangedInstance(DependencyPropertyChangedEventArgs e)
        {
            WineListViewModel wineListViewModel = DataContext as WineListViewModel;
            if (wineListViewModel != null) {
                if (e.NewValue is IEnumerable) {
                    wineListViewModel.Products = e.NewValue as IEnumerable;
                }
            }
        }
    }
}
